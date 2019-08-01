#include "ScapeGUIMouseState.h"
#include "ScapeGUIRendering.h"
#include "ScapeGUIWindowWidgets.h"

#include "UserInputManager.h"

namespace sgeui {
	Component* affectedComponent = nullptr;

	bool mouseIsInArea(Component* c) {
		const Point2D bl = { c->pos().x, c->pos().y + c->dimensions().second };
		const Point2D ur = { c->pos().x + c->dimensions().first, c->pos().y  };

		const int mX = mousePosX;
		const int mY = mousePosY;

		if (mX > bl.x && mX < ur.x) {
			if (mY < bl.y && mY > ur.y) {
				//We've got a hit!
				return true;
			}
		}

		return false;
	}

	inline void sendHoverLostEvent() {
		if (!affectedComponent) {
			return;
		}

		RAISE_EVENT(affectedComponent, new HoverLostEvent(affectedComponent));
		affectedComponent->intDesc.hovered = false;

		affectedComponent = nullptr;
	}

	bool checkChildrenOnMousePosChange(int mouseX, int mouseY, Component* w) {
		bool retval = false;
		//Starting from the back, check if any of the window's children
		//are affected
		for (auto comp = w->children_.rbegin(); comp < w->children_.rend(); comp++) {
			if (mouseIsInArea(*comp)) {
				//The mouse is in the area of the component;
				//Recursively narrow down the affected components
				if (!checkChildrenOnMousePosChange(mouseX, mouseY, *comp)) {
					//Ok, nothing further found, this is the affected one

					if (!(*comp)->intDesc.render) {
						//...except it isn't, because it's not even visible
						continue;
					}

					//First notify the previously hovered component that it is not being
					//hovered anymore
					if (affectedComponent && affectedComponent != *comp) {
						sendHoverLostEvent();
					}

					//Now notify the new one
					affectedComponent = *comp;
					affectedComponent->intDesc.hovered = true;
					
					RAISE_EVENT(affectedComponent, new HoverEvent(affectedComponent));

					retval = true;
				}
			}
		}

		return retval;
	}

	void updateStateOnMousePosChange(int mouseX, int mouseY) {
		//Starting from the back (from the front of the screen)
		//check the first component that is affected

		for (auto windIt = windows.rbegin(); windIt < windows.rend(); windIt++) {
			if (mouseIsInArea(*windIt)) {
				//The affected component is in this window

				if (!checkChildrenOnMousePosChange(mouseX, mouseY, *windIt)) {
					//None was found
					if (!affectedComponent) {
						return;
					}

					sendHoverLostEvent();
				}
				return;
			}
		}

		//Absolutely nothing is being hovered
		sendHoverLostEvent();
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
		//updateStateOnMouseButtonChange(key, pressed);
	}
}

/*namespace sgeui {
	int defaultInteractMouseButton = GLFW_MOUSE_BUTTON_1;
	RenderableQuad* affectedRQ = nullptr;
	ClickState clickState = ClickState::NONE;

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
		ClickState currentState = ClickState::NONE;

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

	ClickState getClickState(RenderableQuad* rq) {
		if (affectedRQ == rq) {
			return clickState;
		}
		else {
			return ClickState::NONE;
		}
	}
}*/
