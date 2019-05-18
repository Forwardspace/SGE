#include "ScapeGUI.h"

namespace sgeui {
	void init(GLFWwindow* wind, int w, int h, Style::Enum style) { 
		initSGEUI(wind, w, h, style);
	}

	void update() {
		setVertexPtrs();
	}
}