#include "ScapeGUIComponent.h"

namespace sgeui {
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

	inline void Component::removeChild(Component* child) {
		auto pos = std::find(children_.begin(), children_.end(), child);
		if (pos != std::end(children_)) {
			children_.erase(pos);
		}
	}

	bool forwardEventToChildren(Component* c, Event* e) {
		for (auto& child : c->children_) {
			if (!FORWARD_EVENT(child, e)) {
				return false;
			}
		}

		return true;
	}
}