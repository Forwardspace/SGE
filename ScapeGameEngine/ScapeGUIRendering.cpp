#include "ScapeGUIRendering.h"

namespace sgeui {
	void RenderableQuad::addChild(RenderableQuad* c) {
		children.push_back(c);
		c->parent = this;
	}

	void RenderableQuad::removeChild(RenderableQuad* c) {
		for (int i = 0; i < children.size(); i++) {
			if (c == children[i]) {
				children[i]->parent = nullptr; //Abandon the child
				children.erase(children.begin() + i);
			}
		}
	}

	void RenderableQuad::render() {
		//First render this object
		update();
		if (render_) {
			auto tx = 
				packedTexture_ ? packedTextures[textureIndex_] : textures[textureIndex_];
			renderQuad(blBound_, urBound_, UVblBound_, UVurBound_, tx, x_, y_);
		}

		//Then render all the children
		if (children.size() > 0) {
			for (auto child : children) {
				child->render();
			}
		}
	}

	void RenderableQuad::moveBy(int x, int y) {
		blBound_ = { blBound_.x + (float)x / windW, blBound_.y + (float)y / windH };
		urBound_ = { urBound_.x + (float)x / windW, urBound_.y + (float)y / windH };

		//Forward the change to all children
		for (auto& child : children) {
			child->moveBy(x, y);
		}
	}

	//Set UVs of a rect to either (if upper) the upper half of the texture
	//or (if not upper) the bottom half.
	void halveUVs(RenderableQuad* r, bool upper) {
		if (upper) {
			r->setUVBounds({ 0, 0.5 }, { 1, 1 });
		}
		else {
			r->setUVBounds({ 0, 0.5 }, { 1, 0.5 });
		}
	}

	const char* translate_uniform = "translate";

	void renderQuad(
		Point2D bl,
		Point2D ur,
		Point2D UVbl,
		Point2D UVur,
		sge::Texture* tx,
		int xP,
		int yP
	) {
		//Similar to sge::StaticObject::render
		//Activate the GUI shader program, bind the texture
		sge::ShaderManager::pushActive(GUIShaderProgram);
		sge::ShaderManager::bindSamplerTexUnit(0);

		sge::TextureManager::bindTexture(tx);

		//Convert pixel coords to ratios
		float x = (float)xP / windW;
		float y = (float)yP / windH;

		//This will generate a rectangle bounded
		//by these points
		PointArray pa = { { bl.x, bl.y }, { ur.x, ur.y }, { bl.x, ur.y }, { ur.x, bl.y } };
		IndexArray ia = { 0, 3, 2, 3, 1, 2 };
		UVArray ua = { { UVbl.x, UVbl.y }, { UVur.x, UVur.y }, { UVbl.x, UVur.y }, { UVur.x, UVbl.y } };

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
		GLint translate_uniform_location = glGetUniformLocation(
			GUIShaderProgram.handle(),
			translate_uniform
		);
		if (translate_uniform_location < 0) {
			throw std::runtime_error("GUI: Can't find translate uniform location!");
		}

		glUniformMatrix4fv(
			translate_uniform_location,
			1, GL_FALSE,
			&translate[0][0]
		);

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

		auto b = glGetError();
		//And finally, issue the draw command:
		glDrawElements(GL_TRIANGLES, (GLsizei)(ia.size()), GL_UNSIGNED_INT, (void*)0);
		auto a = glGetError();
		sge::ShaderManager::popActive();
	}

	std::array<glm::vec2, 4> quadUVsFromTwoPoints(glm::vec2 bl, glm::vec2 ur) {
		return { bl, ur, { bl.x, ur.y }, { ur.x, bl.y } };
	}
}