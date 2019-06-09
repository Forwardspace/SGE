#pragma once
#include "ScapeGUIRendering.h"
#include "ScapeGUIInit.h"

#include "PackedTexture.h"
#include "UserInputManager.h"

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

	namespace ClickState {
		enum Enum {
			NONE,
			HOVER,
			CLICKED,
			AWAITING_BUTTON_RELEASE,
			CLICK_AND_DRAG
		};
	}

	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	bool hit(Point2D bl, Point2D ur);
	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	//and the left mouse button is clicked
	ClickState::Enum getClickState(Point2D bl, Point2D ur, bool& awaitingButtonRelease, bool draggable);
}