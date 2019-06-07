#pragma once
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"

#include "PackedTexture.h"
#include "GLFWIOManager.h"

namespace sgeui {
	extern int windW, windH;

	extern int defaultInteractMouseButton;

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

	extern std::vector<Window*> windows;

	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	bool hit(Point2D bl, Point2D ur);
	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	//and the left mouse button is clicked
	bool clickedOn(Point2D bl, Point2D ur, bool& awaitingLMBRelease);
}