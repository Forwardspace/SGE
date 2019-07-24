#include "ScapeGUIRendering.h"

namespace sgeui {
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
			GUIShaderProgram.handle(),
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

	//Convert pixel coords to OpenGL screen-space coords
	inline float pxToSS(int px, int dim) {
		return 2.0f * (px + 0.5f) / dim - 1.0f;
	}

	#define PTOSX(x) pxToSS(x, windW)
	#define PTOSY(y) pxToSS(y, windH)

	void Renderer::renderQuad(RedrawEvent re, RenderableComponent* comp) {
		glGetError();
		//Quite similar to sge::StaticObject::render

		//Activate the GUI shader program, bind the texture
		setupShadersForRendering(comp->textureResource());

		auto pos = comp->pos();
		auto dim = comp->dimensions();

		auto uv = comp->uvBounds();

		//Convert pixel coords to screen-space ratios
		float x = PTOSX(pos.x);
		float y = PTOSY(pos.y);

		Point2D bl = { PTOSX(x), PTOSY(y + dim.second) };
		Point2D ur = { PTOSX(x + dim.first), PTOSY(y) };

		//This will generate a rectangle bounded
		//by these points
		PointArray pa = { { bl.x, bl.y }, { ur.x, ur.y }, { bl.x, ur.y }, { ur.x, bl.y } };
		IndexArray ia = { 0, 3, 2, 3, 1, 2 };
		UVArray ua = {
			{ uv.first.x, uv.first.y },
			{ uv.second.x, uv.second.y },
			{ uv.first.x, uv.second.y },
			{ uv.second.x, uv.first.y }
		};

		//Generate the translate matrix (no need for
		//the whole MVP matrix
		glm::mat4x4 translate = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, 0, 1
		};

		//Give it to the shader (manually set the
		//translate uniform in the shader)
		sendMatrixToShaders(translate);

		//Now for the buffers:
		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, sge::BufferManager::VBO(sge::VBOType::UV));
		glBufferData(
			GL_ARRAY_BUFFER,
			ua.size() * sizeof(Point2D),
			ua.data(),
			GL_STATIC_DRAW
		);
		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, sge::BufferManager::VBO(sge::VBOType::VERTEX2D));
		glBufferData(
			GL_ARRAY_BUFFER,
			pa.size() * sizeof(Point2D),
			pa.data(),
			GL_STATIC_DRAW
		);
		//Indices
		//The index array is already bound
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			ia.size() * sizeof(GLuint),
			ia.data(),
			GL_STATIC_DRAW
		);

		//And finally, issue the draw command:
		glDrawElements(GL_TRIANGLES, (GLsizei)(ia.size()), GL_UNSIGNED_INT, (void*)0);

		sge::ShaderManager::popActive();

		auto e = glGetError();
		if (e != 0) {
			//Something's wrong
			std::cout << "glGetError() returned non-zero in renderQuad(): errno " << e << "!\n";
		}
	}
}