#pragma once
#include "ScapeGUI.h"

namespace sgeui {
	namespace ClickState {
		enum Enum {
			NONE,
			HOVER,
			CLICKED,
			AWAITING_BUTTON_RELEASE,
			CLICK_AND_DRAG
		};
	}

	void updateClickStates();
	ClickState::Enum getClickState(RenderableQuad* rq);

	//////
	extern RenderableQuad* affectedRQ;
	extern ClickState::Enum clickState;
	//////

	extern int defaultInteractMouseButton;
}