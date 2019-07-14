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
		virtual void get() {}
	};

	struct StaticTextureResource {
		inline sge::Texture* get() { return texture; }

	private:
		sge::Texture* texture;
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