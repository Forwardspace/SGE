#include "ScapeGUIComponent.h"

namespace sgeui {
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
			child->moveTo(x, y);
		}
	}

	void Component::moveBy(int x, int y) {
		x_ += x;
		y_ += y;

		for (auto& child : children_) {
			child->moveBy(x, y);
		}
	}

	inline void Component::addChild(Component* child) {
		children_.push_back(child);
	}

	inline void Component::removeChild(Component* child) {
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