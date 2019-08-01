#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "EventHandling.h"

#include "ScapeGUITypes.h"
#include "ScapeGUIInit.h"

namespace sgeui {
	class Component;
	bool forwardEventToChildren(Component* c, Event* e);

	struct InteractionDescriptor {
		bool render = true;
		bool isHoverable = false;
		bool isClickable = false;
		bool isDraggable = false;

		//These are primarily for ...MouseState.cpp
		bool mouseIsDown = false;
		bool hovered = false;
	};

	class Component {
	public:
		LISTENER;

		Component(int x, int y, int width, int height) : LISTENER_INIT(forwardEventToChildren), x_(x), y_(y), width_(width), height_(height) {}
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
		inline void setUvBounds(std::array<glm::vec2, 2> uvs) { uvBl_ = uvs[0], uvUr_ = uvs[1]; }
		inline Pair<Point2D, Point2D> uvBounds() { return { uvBl_, uvUr_ }; }
		///
		inline void addChild(Component* child) { children_.push_back(child); };
		inline void removeChild(Component* child);
		inline std::vector<Component*> children() { return children_; }

		//How does this component interact with input and output?
		//false: do not try to render this
		InteractionDescriptor intDesc{ false };
		
	protected:
		const bool isQuad = true;

		int width_;
		int height_;

		//The screen-space position
		int x_, y_;
		Point2D	uvBl_, uvUr_;

		std::vector<Component*> children_;

		friend bool forwardEventToChildren(Component* c, Event* e);
		friend bool checkChildrenOnMousePosChange(int mouseX, int mouseY, Component* w);
	};

	class RenderableComponent : public Component {
	public:
		RenderableComponent(int x, int y, int width, int height, TextureResource* rsc) : 
			Component(x, y, width, height), rsc_(rsc) {
			
			HANDLES_EVENT(Redraw);

			intDesc.render = true;
		}
		///
		EVENT_HANDLER(Redraw, {
			//Draw this on the screen
			event->calleeIsQuad = true;
			event->target = this;
			RAISE_MASTER_EVENT(event);

			return true;
		});
		///
		inline void setTextureResource(TextureResource* rsc) { rsc_ = rsc; }
		inline TextureResource* textureResource() { return rsc_; }
		///
		inline bool render(Component* source = nullptr) { return RAISE_EVENT(this, new RedrawEvent(true, true)); }

	protected:
		TextureResource* rsc_ = nullptr;
	};
}