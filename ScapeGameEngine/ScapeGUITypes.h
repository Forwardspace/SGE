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

	class Component;
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

	struct FocusEvent : public Event { FocusEvent() { REGISTER_EVENT(FocusEvent) } };
	struct UnfocusEvent : public Event { UnfocusEvent() { REGISTER_EVENT(UnfocusEvent) } };

	struct HoverEvent : public Event { 
		HoverEvent() { REGISTER_EVENT(HoverEvent); } 
	};
	struct HoverLostEvent : public Event {
		HoverLostEvent() { REGISTER_EVENT(HoverLostEvent); }
	};

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

	struct ClickEvent : public Event {
		ClickEvent(int x, int y) : mX(x), mY(y) { REGISTER_EVENT(ClickEvent) }
		//Mouse pos when the click happened
		int mX, mY;
	};
	
	struct DragStartEvent : public Event {
		DragStartEvent(int x, int y) : oldX(x), oldY(y) { REGISTER_EVENT(DragStartEvent) }
		//The starting mouse position
		int oldX, oldY;
	};
	struct DragEvent : public Event {
		DragEvent(int x, int y) : newX(x), newY(y) { REGISTER_EVENT(DragEvent) }
		//The new mouse position
		int newX, newY;
	};

	extern EventHandler masterEH;
}