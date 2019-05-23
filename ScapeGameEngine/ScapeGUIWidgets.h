#pragma once
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"

namespace sgeui {
	class Window : public Renderable {
	public:
		Window();
		Window(int w, int h, int xPos, int yPos);
		~Window();
	private:
		int h_ = 0, w_ = 0;
	};
}