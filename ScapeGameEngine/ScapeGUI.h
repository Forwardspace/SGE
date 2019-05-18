#pragma once
#include "stdheaders.h"
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"
#include "ScapeGUITypes.h"

namespace sgeui {
	void init(GLFWwindow* wind, int w, int h, Style::Enum style);
	void update();
}