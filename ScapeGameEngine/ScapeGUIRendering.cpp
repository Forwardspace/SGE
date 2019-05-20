#include "ScapeGUIRendering.h"

namespace sgeui {
	void Renderable::addChild(Renderable & c) {
		children.push_back(&c);
		c.parent = this;
	}

	void Renderable::removeChild(Renderable & c) {
		for (int i = 0; i < children.size(); i++) {
			if (&c == children[i]) {
				children[i]->parent = nullptr; //Abandon the child
				children.erase(children.begin() + i);
			}
		}
	}

	void Renderable::render() {
		//First render this object
		renderPoly(pa_, ia_, ua_, tx_, x_, y_);

		//Then render all the children
		if (children.size() > 0) {
			for (auto child : children) {
				child->render();
			}
		}
	}

	//Provided a bottom left and an upper right point,
	//this will generate a renderable rectangle bounded
	//by these points
	Renderable rectFromTwoPoints(Point2D bl, Point2D ur) {
		//Generate two triangles and all corresponding data
		PointArray pa = { { bl.x, bl.y }, { ur.x, ur.y }, { bl.x, ur.y }, { ur.x, bl.y } };
		IndexArray ia = { 0, 3, 2, 3, 1, 2 };
		UVArray ua = { { 0, 0 }, { 1, 1 }, { 0, 1 }, { 1, 0 } };

		Renderable rectangle(pa, ia, ua);
		return rectangle;
	}

	const char* translate_uniform = "translate";

	void renderPoly(
		PointArray& pa,
		IndexArray& ia,
		UVArray& ua,
		sge::Texture& tx,
		float xP,
		float yP
	) {
		//Similar to sge::StaticObject::render
		//Activate the GUI shader program, bind the texture
		sge::ShaderManager::pushActive(GUIShaderProgram);
		sge::ShaderManager::bindSamplerTexUnit(0);

		sge::TextureManager::bindTexture(&tx);

		//Convert pixel coords to ratios
		float x = xP / w;
		float y = yP / h;

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

		//And finally, issue the draw command:
		glDrawElements(GL_TRIANGLES, (GLsizei)(ia.size()), GL_UNSIGNED_INT, (void*)0);

		sge::ShaderManager::popActive();
	}
}