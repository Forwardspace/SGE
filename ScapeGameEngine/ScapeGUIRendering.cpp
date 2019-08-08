#include "ScapeGUIRendering.h"

namespace sgeui {
	extern GLuint buffs[3];

	void setupShadersForRendering(TextureResource* tx) {
		//Similar to sge::StaticObject::render
		//Activate the GUI shader program, bind the texture
		sge::ShaderManager::pushActive(*GUIShaderProgram);
		sge::ShaderManager::bindSamplerTexUnit(0);

		sge::TextureManager::bindTexture(tx? tx->get() : nullptr);
	}

	char* translate_uniform_name = "translate";

	void sendMatrixToShaders(glm::mat4x4& translate) {
		GLint translate_uniform_location = glGetUniformLocation(
			GUIShaderProgram->handle(),
			translate_uniform_name
		);
		if (translate_uniform_location < 0) {
			throw std::runtime_error("GUI Error: Can't find translate uniform location!");
		}

		glUniformMatrix4fv(
			translate_uniform_location,
			1, GL_FALSE,
			&translate[0][0]
		);
	}

	void renderQuad(RedrawEvent re, RenderableComponent* comp) {
		glGetError();

		sge::BufferManager::bindVAO(SGEUI_BUFFER_ID);

		//Todo: optimize using glBufferSubdata
		//do not forget to resize the buffers optimally

		//Activate the GUI shader program, bind the texture
		setupShadersForRendering(comp->textureResource());

		auto pos = comp->pos();
		auto dim = comp->dimensions();

		auto uv = comp->uvBounds();

		Point2D bl = { 0, (float)dim.second };
		Point2D ur = { (float)dim.first, 0 };

		//This will generate a rectangle bounded
		//by these points
		PointArray pa = { { bl.x, bl.y }, { ur.x, ur.y }, { bl.x, ur.y }, { ur.x, bl.y } };
		const IndexArray ia = { 0, 3, 2, 3, 1, 2 };
		UVArray ua = {
			{ uv.first.x, uv.first.y },
			{ uv.second.x, uv.second.y },
			{ uv.first.x, uv.second.y },
			{ uv.second.x, uv.first.y }
		};

		//Generate the orthographic projection matrix (projects screen space to normalized coords)
		auto ortho = glm::ortho(0.f, (float)windW, (float)windH, 0.f, -1.f, 1.f);

		//Generate the translate matrix (no need for
		//the whole MVP matrix, no scaling or rotation)
		glm::mat4x4 translate = {
			1,	   0,     0, 0,
			0,	   1,     0, 0,
			0,	   0,     1, 0,
			pos.x, pos.y, 0, 1
		};

		//Combine them...
		ortho *= translate;

		//Give it to the shader (manually set the
		//translate uniform in the shader)
		sendMatrixToShaders(ortho);

		//Now for the buffers. Note: ScapeGUI does not append data directly
		//Because the efficiency benefit in this instance is not that significant
		//Vertices
		glNamedBufferData(
			buffs[0],
			pa.size() * sizeof(Point2D),
			pa.data(),
			GL_STATIC_DRAW
		);
		//Texture coords
		glNamedBufferData(
			buffs[1],
			ua.size() * sizeof(Point2D),
			ua.data(),
			GL_STATIC_DRAW
		);
		//Indices
		glNamedBufferData(
			buffs[2],
			6 * sizeof(GLuint),		//6 indices in total
			ia.data(),
			GL_STATIC_DRAW
		);

		auto a = glGetError();

		//And finally, issue the draw command:
		glDrawElements(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_INT, (void*)0);

		sge::ShaderManager::popActive();

		auto e = glGetError();
		if (e != 0) {
			//Something's wrong
			std::cout << "glGetError() returned non-zero in renderQuad(): errno " << e << "!\n";
		}
	}
}