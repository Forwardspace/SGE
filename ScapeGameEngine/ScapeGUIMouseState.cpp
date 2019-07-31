#include "ScapeGUIMouseState.h"
#include "ScapeGUIRendering.h"
#include "ScapeGUIWindowWidgets.h"

#include "GLFWIOManager.h"

/*namespace sgeui {
	int defaultInteractMouseButton = GLFW_MOUSE_BUTTON_1;
	RenderableQuad* affectedRQ = nullptr;
	ClickState::Enum clickState = ClickState::NONE;

	inline bool mouseClicked() {
		return sge::GLFWIOManager::mouseKeyStatus(defaultInteractMouseButton);
	}

	RenderableQuad* draggedRenderable = nullptr;
	
	bool doneWithUpdate = false;

	//Find what the mouse status has in relation with RQ
	//by predicting the state and eliminating possibilities
	//Stop when an important state has been reached
	void updateClickState(RenderableQuad* rq) {
		static bool awaitingButtonRelease = false;

		bool hits = hit(rq->bl(), rq->ur());
		ClickState::Enum currentState = ClickState::NONE;

		if (!rq->renderRenderable) {
			//Invisible renderables are not affected
			//Don't look
			goto done;
		}

		if (hits) {
			//Current best prediction - HOVER
			currentState = ClickState::HOVER;

			if (mouseClicked()) {
				//OK, not hover, could be drag or ABR
				currentState = ClickState::AWAITING_BUTTON_RELEASE;
				awaitingButtonRelease = true;

				if (rq->draggable) {
					//Drag event only if RQ has been previously dragged
					//or nothing has been dragged
					if (draggedRenderable == rq || draggedRenderable == nullptr) {
						currentState = ClickState::CLICK_AND_DRAG;
						//doneWithUpdate = true;

						draggedRenderable = rq;
					}
					else {
						currentState = ClickState::NONE;
					}
				}
			}
			else {
				//Maybe a click?
				if (awaitingButtonRelease) {
					//Yup
					currentState = ClickState::CLICKED;
					awaitingButtonRelease = false;
					//doneWithUpdate = true;
				}
			}
		}
		else {
			if (draggedRenderable == rq) {
				if (mouseClicked()) {
					//Drag
					currentState = ClickState::CLICK_AND_DRAG;
					//doneWithUpdate = true;
				}
				else {
					//Not dragging anymore
					draggedRenderable = nullptr;
					awaitingButtonRelease = false;
				}
			}
			else {
				if (draggedRenderable != nullptr) {
					if (!mouseClicked()) {
						//Not dragging
						draggedRenderable = nullptr;
						awaitingButtonRelease = false;
					}
				}
			}
		}
		
		if (currentState != ClickState::NONE) {
			if (clickState == ClickState::HOVER || 
				clickState == ClickState::NONE || 
				clickState == ClickState::AWAITING_BUTTON_RELEASE
			) {
				clickState = currentState;
				affectedRQ = rq;
			}
		}

		//BUG: HOVER state does not register properly
		//TODO: fix

	done:

		//Recursively update all children, in reverse order
		//(topmost first)
		auto children = rq->getChildren();
		for (auto i = children.rbegin(); i < children.rend(); i++) {
			updateClickState(*i);
		}
	}

	void updateClickStates() {
		doneWithUpdate = false;
		clickState = ClickState::NONE;
		affectedRQ = nullptr;

		//Basically, go from the top of the windows down and
		//check what is the first Window that is affected by the mouse
		for (auto w = windows.rbegin(); w != windows.rend(); w++) {
			updateClickState(*w);

			if (doneWithUpdate) {
				return;
			}
		}
	}

	ClickState::Enum getClickState(RenderableQuad* rq) {
		if (affectedRQ == rq) {
			return clickState;
		}
		else {
			return ClickState::NONE;
		}
	}
}*/