#pragma once
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"
#include "PackedTexture.h"

namespace sgeui {
	class Window : public RenderableQuad{
	public:
		Window();
		Window(int w, int h, int xPos, int yPos);
		~Window();
	private:
		int h_ = 0, w_ = 0;
	};

	//That thing with the close button in the top right
	class WindowHelper : public RenderableQuad {
	public:
		WindowHelper(Point2D bl, Point2D ur);

		void update();
	private:
	};

	extern std::list<Window*> windows;
}