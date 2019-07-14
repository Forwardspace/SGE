#include "ScapeGUI.h"

namespace sgeui {
	const extern int numMouseButtons;

	extern int mousePosX, mousePosY;
	extern std::array<bool, 8> mouseButtons;

	void init(GLFWwindow* wind, int w, int h) { 
		initSGEUI(wind, w, h);
	}

	void render() {
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

	void onMousePosUpdate(int mouseX, int mouseY) {
		mousePosX = mouseX;
		mousePosY = mouseY;

		//Update the internal states of all Components
		updateStateOnMousePosChange(mouseX, mouseY);
	}
	
	void onMouseButtonUpdate(int key, bool pressed) {
		mouseButtons[key] = pressed;

		//Update all of the positions, relations and states of all Components
		updateStateOnMouseButtonChange(key, pressed);
	}

	std::vector<Window*> windows;
}