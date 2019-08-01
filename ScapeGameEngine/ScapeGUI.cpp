#include "ScapeGUI.h"
#include "ScapeGUIInit.h"

namespace sgeui {
	const extern int numMouseButtons;
	std::array<bool, numMouseButtons> mouseButtons;

	MASTER_LISTENER;

	MASTER_EVENT_HANDLER(Redraw, {
			if (!event->target) {
				//Well, there's really nothing to draw, is there?
				throw std::runtime_error("Error: GUI RedrawEvent target is nullptr at the time of handling!");
			}
			if (event->target->intDesc.render) {
				if (event->calleeIsQuad) {
					renderQuad(*event, event->target);
				}
				else {
					//renderWeirdlyShapedComponent(...);
				}
			}

			return true;
	});

	int defaultInteractMouseButton = GLFW_MOUSE_BUTTON_1;
	int mousePosX = 0, mousePosY = 0;

	void init(GLFWwindow* wind, int w, int h) {
		initSGEUI(wind, w, h);

		MASTER_HANDLES_EVENT(Redraw);
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
		for (auto w : windows) {
			RAISE_EVENT(w, new RedrawEvent(true, false));
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}