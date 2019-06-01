#include "ScapeGUI.h"

namespace sgeui {
	void init(GLFWwindow* wind, int w, int h) { 
		initSGEUI(wind, w, h);
	}

	void update() {
		//Disable depth and culling and enable transparency
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		setVertexPtrs();

		//Recursively render all elements
		for (auto& window : windows) {
			window->render();
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	std::list<Window*> windows;
}