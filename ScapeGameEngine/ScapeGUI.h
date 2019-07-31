#pragma once
#include "stdheaders.h"
#include "ScapeGUITypes.h"
#include "ScapeGUIWindowWidgets.h"
#include "ScapeGUIComponent.h"
#include "ScapeGUIRendering.h"

#include "EventHandling.h"

namespace sgeui {
	const int numMouseButtons = GLFW_MOUSE_BUTTON_LAST + 1;
	extern std::array<bool, numMouseButtons> mouseButtons;

	extern int defaultInteractMouseButton;

	extern int mousePosX, mousePosY;

	void init(GLFWwindow* wind, int w, int h);
	void render();

	void onMousePosUpdate(int posX, int posY);
	void onMouseButtonUpdate(int button, bool pressed);
}