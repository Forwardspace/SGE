#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "EventHandling.h"

namespace sgeui {
	struct Point2D {
		float x = 0, y = 0;

		glm::vec2 operator=(glm::vec2 v) { x = v.x; y = v.y; return v; }
	};

	//Screen point 2D
	struct SPoint2D {
		int x = 0, y = 0;
	};

	struct TexCol {
		GLbyte r = 0, g = 0, b = 0, a = 0;
	};

	template<typename T1, typename T2>
	struct Pair {
		Pair(T1 val1, T2 val2) {
			first = val1;
			second = val2;
		}

		T1 first;
		T2 second;
	};

	struct TextureResource {
		virtual sge::Texture* get() { return nullptr; }
		virtual std::string name() { return name_; }

		virtual ~TextureResource() {}

	protected:
		std::string name_ = "<Base_class>";
	};

	struct StaticTextureResource : public TextureResource {
	public:
		StaticTextureResource(sge::Texture* t, std::string name) : texture_(t) { name_ = name; }
		StaticTextureResource(fs::path p, std::string name) { texture_ = new sge::Texture(p); name_ = name; }

		inline sge::Texture* get() { return texture_; }

		virtual ~StaticTextureResource() { delete texture_; }

	protected:
		sge::Texture* texture_;
	};

	struct ThemeTextureResource : public StaticTextureResource {
	public:
		ThemeTextureResource(sge::Texture* t, std::string name) : StaticTextureResource(t, name) { }
		ThemeTextureResource(fs::path p, std::string name) : StaticTextureResource(p, name) { }
	};

	using Theme = ThemeTextureResource;

	using PointArray = std::vector<Point2D>;
	using IndexArray = std::vector<GLuint>;
	using UVArray = PointArray;

	class RenderableComponent;

	///// EVENTS ////
	struct RedrawEvent : public Event {
		RedrawEvent(bool rc, bool ciq, RenderableComponent* r = nullptr) : 
			renderChildren(rc), calleeIsQuad(ciq), target(r) {
			REGISTER_EVENT(RedrawEvent)
		}
		bool renderChildren;
		bool calleeIsQuad;
		RenderableComponent* target;
	};

	struct FocusedEvent : public Event { FocusedEvent() { REGISTER_EVENT(FocusedEvent) } };
	struct UnfocusedEvent : public Event { UnfocusedEvent() { REGISTER_EVENT(UnfocusedEvent) } };

	struct MouseDownEvent : public Event {
		MouseDownEvent(int x, int y) : mX(x), mY(y) { REGISTER_EVENT(MouseDownEvent) }
		//Mouse pos when the MouseDown happened
		int mX, mY;
	};
	struct MouseUpEvent : public Event {
		MouseUpEvent(int x, int y) : mX(x), mY(y) { REGISTER_EVENT(MouseUpEvent) }
		//Mouse pos when the MouseDown happened
		int mX, mY;
	};

	struct ClickedEvent : public Event {
		ClickedEvent(int x, int y) : mX(x), mY(y) { REGISTER_EVENT(ClickedEvent) }
		//Mouse pos when the click happened
		int mX, mY;
	};
	struct DraggedEvent : public Event {
		DraggedEvent(int x, int y) : newX(x), newY(y) { REGISTER_EVENT(DraggedEvent) }
		//The new position
		int newX, newY;
	};

	extern EventHandler masterEH;
}