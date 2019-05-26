#include "ScapeGUI.h"

namespace sgeui {
	void init(GLFWwindow* wind, int w, int h, Style::Enum style) { 
		initSGEUI(wind, w, h, style);
	}

	void update() {
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		setVertexPtrs();

		//lDisable(GL_CULL_FACE);
		//glDisable(GL_DEPTH_TEST);
	}
}