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

	void renderPoly(
		PointArray& pa,
		IndexArray& ia,
		UVArray& ua,
		sge::Texture& tx,
		float xP,
		float yP
	) {
		//Convert pixel coords to ratios
		float x = xP / w;
		float y = yP / h;

		//Generate the transform matrix (no need for
		//the whole MVP matrix
		glm::mat3x3 transform = { 
			1, 0, x,
			0, 1, y,
			0, 0, 1
		};

		//Now give it to the shader
		

		//Bind the texture...

		//Now for the buffers:

		//And finally:
	}
}