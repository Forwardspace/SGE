#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BufferManager.h"

#include "ScapeGUITypes.h"
#include "ScapeGUIInit.h"

namespace sgeui {
	struct InteractionDescriptor {
		bool render = true;
		bool isHoverable = false;
		bool isClickable = false;
		bool isDraggable = false;

		bool mouseIsDown = false;
	};

	class Component {
	public:
		Component(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {}
		Component() {}
		///
		virtual bool handleEvent(Event e, Component* source);
		///
		void raiseEvent(Event t, Component* s);
		///
		inline void setDimensions(int width, int height) { width_ = width; height_ = height; }
		//First: width, second: height
		inline Pair<int, int> dimensions() { return { width_, height_ }; }
		///
		inline void setPos(int x, int y) { x_ = x; y_ = y; }
		inline SPoint2D pos() { return { x_, y_ }; }

		void moveTo(int x, int y);
		void moveBy(int x, int y);
		///
		inline void setUvBounds(Point2D bl, Point2D ur) { uvBl_ = bl; uvUr_ = ur; }
		inline Pair<Point2D, Point2D> uvBounds() { return { uvBl_, uvUr_ }; }
		///
		inline void addChild(Component* child);
		inline void removeChild(Component* child);
		inline std::vector<Component*> children() { return children_; }

		//How does this component interact with input
		InteractionDescriptor intDesc;

	protected:
		const bool isQuad = true;

		int width_;
		int height_;

		//The screen-space position
		int x_, y_;
		Point2D	uvBl_, uvUr_;

		std::vector<Component*> children_;

		template<class EventType>
		inline bool forwardEventToChildren(EventType t, Component* s) {
			for (auto child : children_) {
				if (!child->handleEvent(t, s)) {
					return false;
				}

				return true;
			}
		}
	};

	class RenderableComponent : public Component {
	public:
		RenderableComponent(int x, int y, int width, int height, TextureResource* rsc) : 
			Component(x, y, width, height), rsc_(rsc) {}
		RenderableComponent() {}

		bool handleEvent(Event e, Component* source);
		bool handleEvent(RedrawEvent e, Component* source);
		///
		inline void setTextureResource(TextureResource* rsc) { rsc_ = rsc; }
		inline TextureResource* textureResource() { return rsc_; }

		inline bool render(Component* source = nullptr) { return handleEvent(RedrawEvent(true, false), source); }

	protected:
		TextureResource* rsc_ = nullptr;
	};

	template<class EventType>
	extern void masterHandleEvent(EventType re, Component* callee);

	template<>
	extern void masterHandleEvent<RedrawEvent>(RedrawEvent re, Component* callee);
}