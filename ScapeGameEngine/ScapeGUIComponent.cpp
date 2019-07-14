#include "ScapeGUIComponent.h"

namespace sgeui {
	/*
	//Set UVs of a rect to either (if upper) the upper half of the texture
	//or (if not upper) the bottom half.
	void halveUVs(RenderableQuad* r, bool upper) {
		if (upper) {
			r->setUVBounds({ 0, 0.5 }, { 1, 1 });
		}
		else {
			r->setUVBounds({ 0, 0.5 }, { 1, 0.5 });
		}
	}
	*/

	bool Component::handleEvent(Event e, Component* source) {
		return forwardEventToChildren(e, source);
	}

	void Component::raiseEvent(Event t, Component* s) {
		if (s == nullptr) {
			throw std::runtime_error("Error: raiseEvent(t == nullptr, ...). Wait. That's illegal.");
		}
		else {
			s->handleEvent(t, this);
		}
	}

	void Component::moveTo(int x, int y) {
		x_ = x;
		y_ = y;

		for (auto& child : children_) {
			child.moveTo(x, y);
		}
	}

	void Component::moveBy(int x, int y) {
		x_ += x;
		y_ += y;

		for (auto& child : children_) {
			child.moveBy(x, y);
		}
	}

	inline void Component::addChild(Component& child) {
		children_.push_back(child);
	}

	inline void Component::removeChild(Component& child) {
		auto pos = std::find(children_.begin(), children_.end(), child);
		if (pos != std::end(children_)) {
			children_.erase(pos);
		}
	}

	///

	bool RenderableComponent::handleEvent(Event r, Component* source) {
		return forwardEventToChildren<Event>(r, source);
	}

	bool RenderableComponent::handleEvent(RedrawEvent r, Component* source) {
		//Draw this on the screen
		masterHandleEvent<RedrawEvent>(r, this);

		return forwardEventToChildren<RedrawEvent>(r, source);
	}
}