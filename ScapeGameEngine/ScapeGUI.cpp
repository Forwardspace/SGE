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
		updateMouseDelta();

		//Recursively render all elements
		bool render = true;
		int i = 0;
		while (render) {
			size_t size = windows.size();
			if (i >= size) {
				break;
			}

			windows[i]->render();

			//Check if a window has been removed
			if (!(windows.size() < size)) {
				//It hasn't, continue
				i++;
			}
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	std::vector<Window*> windows;
}