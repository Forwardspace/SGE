#pragma once
#include "ScapeGUI.h"

namespace sgeui {
	extern Component* affectedComponent;

	extern void onMousePosUpdate(int posX, int posY);
	extern void onMouseButtonUpdate(int button, bool pressed);

	extern int defaultInteractMouseButton;
}