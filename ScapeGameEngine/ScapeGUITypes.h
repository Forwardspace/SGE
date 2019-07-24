#pragma once

namespace sgeui {
	struct Point2D {
		float x = 0, y = 0;
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

		virtual ~TextureResource() {}
	};

	struct StaticTextureResource : public TextureResource {
	public:
		StaticTextureResource(sge::Texture* t, std::string name) : texture_(t), name_(name) { }
		StaticTextureResource(fs::path p, std::string name) : name_(name) { texture_ = new sge::Texture(p); }

		inline sge::Texture* get() { return texture_; }
		inline std::string name() { return name_; }

		virtual ~StaticTextureResource() { delete texture_; }

	private:
		sge::Texture* texture_;
		std::string name_;
	};

	struct ThemeTextureResource : public StaticTextureResource {
	public:
		ThemeTextureResource(sge::Texture* t, std::string name) : StaticTextureResource(t, name) { }
		ThemeTextureResource(fs::path p, std::string name) : StaticTextureResource(p, name) { }

	private:
		std::string name_ = "";
	};

	using Theme = TextureResource;

	using PointArray = std::vector<Point2D>;
	using IndexArray = std::vector<GLuint>;
	using UVArray = PointArray;

	class RenderableQuad;

	///// EVENTS /////
	struct Event {};

	struct RedrawEvent : public Event {
		RedrawEvent(bool rc, bool ciq) : renderChildren(rc), calleeIsQuad(ciq) {}
		bool renderChildren;
		bool calleeIsQuad;
	};

	struct FocusedEvent : public Event {};
	struct UnfocusedEvent : public Event {};

	struct MouseDownEvent : public Event {
		//Mouse pos when the MouseDown happened
		int mX, mY;
	};
	struct MouseUpEvent : public Event {
		//Mouse pos when the MouseDown happened
		int mX, mY;
	};

	struct ClickedEvent : public Event {
		//Mouse pos when the click happened
		int mX, mY;
	};
	struct DraggedEvent : public Event {
		//The new position
		int newX, newY;
	};
}