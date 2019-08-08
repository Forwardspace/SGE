#pragma once
#include "ScapeGUIComponent.h"
#include "ScapeGUIInit.h"
#include "EventHandling.h"

namespace sgeui {
	extern int windW, windH;
	extern int defaultInteractMouseButton;

	extern int mousePosX, mousePosY;
	class Window;

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int newX, int newY) : newX(newX), newY(newY) { REGISTER_EVENT(WindowResizeEvent) }

		int newX, newY;
	};
	struct WindowShouldCloseEvent : public Event {
		WindowShouldCloseEvent(Window* w) : window(w) { REGISTER_EVENT(WindowShouldCloseEvent) }
		
		Window* window;
	};

	class Window : public Component {
	public:
		Window(int w, int h, int xPos, int yPos);

		~Window();

		void setSize(int w, int h);
		inline Pair<int, int> getSize() { return { width_, height_ }; }

		void scheduleClose();

		EVENT_HANDLER(WindowResize, {
			return true;
		});
	};

	extern std::vector<Window*> windows;

	//This puts the window newOnTop on the back
	//of windows, thus making it appear on top
	//of all other windows
	void swapWindowOnTop(Window* newOnTop);

	//The toolbar (without the toolbar)
	class WindowBanner : public RenderableComponent {
	public:
		WindowBanner(int w, int h, int xPos, int yPos, Window* parent);

		EVENT_HANDLER(DragStart, {
			if (event->target != this) {
				return true;
			}

			//Put the parent window on top
			swapWindowOnTop(parent_);

			dragOriginX = prevDragX = event->oldX;
			dragOriginY = prevDragY = event->oldY;
			return true;
		});
		EVENT_HANDLER(Drag, {
			if (event->target != this) {
				return true;
			}
			//Calculate the delta between the mouse pos at the
			//previous mouse movement and the current mouse pos
			int deltaX = mousePosX - prevDragX;
			int deltaY = mousePosY - prevDragY;

			prevDragX = mousePosX;
			prevDragY = mousePosY;

			parent_->moveBy(deltaX, deltaY);
			return true;
		});
	private:
		Window* parent_;

		int dragOriginX = 0, dragOriginY = 0;
		int prevDragX = 0, prevDragY = 0;
	};

	//The actual main portion of the window
	class WindowSurface : public RenderableComponent {
	public:
		WindowSurface(int w, int h, int xPos, int yPos, Window* parent);

	private:
		Window* parent_;
	};

	//The thing with the close, minimize and maximize buttons
	class WindowHelper : public Component {
	public:
		//x, y is the ur point of the Window
		WindowHelper(int x, int y, Window* parent);

		void closeParent();

	private:
		Window* parent_;
	};

	/*//From ...MouseState.cpp
	extern RenderableQuad* draggedRenderable;

	extern int defaultInteractMouseButton;

	class Window : public RenderableComponent {
	public:
		Window();
		Window(int w, int h, int xPos, int yPos);
		~Window();

		void setSize(int w, int h);
		std::pair<int, int> getSize() { return std::pair<int, int>(h_, w_); }

	private:
		int h_ = 0, w_ = 0;
	};
	
	class WindowBanner : public RenderableComponent {
	public:
		WindowBanner() { draggable = true; }
		WindowBanner(Point2D bl, Point2D ur) { blBound_ = bl; urBound_ = ur; draggable = true; }
		void update();
	};

	//That thing with the close button in the top right
	class WindowHelper : public RenderableComponent {
	public:
		WindowHelper(Point2D bl, Point2D ur);

		void update();

	private:
		void updateCloseButton();
	};

	//Allows you to "snap" windows to predefined locations
	class WindowSnapArea : public RenderableQuad {
	public:
		WindowSnapArea(Point2D bl, Point2D ur, int wX, int wY, int windPosX, int windPosY);

		void update();

	private:
		int wX_ = 0, wY_ = 0;
		int windPosX_, windPosY_;

		Window* windowInArea = nullptr;
		std::pair<int, int> windowPos;
		std::pair<int, int> windowSize;
	};

	extern std::vector<Window*> windows;

	//Returns true if the mouse position is
	//in the rectangle described by bl, ur
	bool hit(Point2D bl, Point2D ur);
	//Returns true if the rectangle (bl, ur) of w1
	//and the rectangle (bl, ur) of w2 share any point
	bool collide(RenderableQuad* r1, RenderableQuad* r2);
	//Swapps target with the window on top of the windows vector.
	void pushWindowOnTop(Window* target);
	*/
}