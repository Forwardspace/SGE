#pragma once
#include "stdheaders.h"
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"
#include "ScapeGUITypes.h"
#include "ScapeGUIWindowWidgets.h"
#include "ScapeGUIComponent.h"

namespace sgeui {
	const int numMouseButtons = GLFW_MOUSE_BUTTON_LAST + 1;

	void init(GLFWwindow* wind, int w, int h);
	void render();

	void onMousePosUpdate(int posX, int posY);
	void onMouseButtonUpdate(int button, bool pressed);

	template<class EventType>
	void masterHandleEvent(EventType re, Component* callee);

	template<>
	void masterHandleEvent<RedrawEvent>(RedrawEvent re, Component* callee);

	//Pointers to all the windows in the GUI, which in turn
	//point to all the other elements to be rendered
	extern std::vector<Window*> windows;
	
	template<class EventType>
	void masterHandleEvent(EventType re, Component* callee) {
		throw std::runtime_error(
			"Critical warning? masterHandleEvent() was called as a non-specialized function." \
			"This most likely means Component* wasn't nullptr on purpose."
		);
	}

	template<>
	void masterHandleEvent<RedrawEvent>(RedrawEvent re, Component* callee) {
		if (re.calleeIsQuad) {
			Renderer::renderQuad(re, static_cast<RenderableComponent*>(callee));
		}
		else {
			//Renderer::renderWeirdlyShapedComponent(re, callee);
		}
	}
}