#pragma once
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"

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
	
	class WindowBanner : public RenderableQuad {
	public:
		WindowBanner() { draggable = true; }
		WindowBanner(Point2D bl, Point2D ur) { blBound_ = bl; urBound_ = ur; draggable = true; }
		void update();
	};

	//That thing with the close button in the top right
	class WindowHelper : public RenderableQuad {
	public:
		WindowHelper(Point2D bl, Point2D ur);

		void update();
	private:
		void updateCloseButton();
	};

	extern std::vector<Window*> windows;

	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	bool hit(Point2D bl, Point2D ur);
	//Returns true if the rectangle (bl, ur) of w1
	//and the rectangle (bl, ur) of w2 share any point
	bool collide(Window* w1, Window* w2);
	//Swapps target with the window on top of the windows vector.
	void pushWindowOnTop(Window* target);
}