#pragma once
#include "stdheaders.h"
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"
#include "ScapeGUITypes.h"
#include "ScapeGUIWidgets.h"

namespace sgeui {
	void init(GLFWwindow* wind, int w, int h);
	void update();

	//Pointers to all the windows in the GUI, which in turn
	//point to all the other elements to be rendered
	extern std::vector<Window*> windows;
}