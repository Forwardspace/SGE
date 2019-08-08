#pragma once
#include "ScapeGUITypes.h"
#include "ScapeGUIComponent.h"

namespace sgeui {
	//A simple configurable button
	//Simply supply it with a location, size, texture and an onPress callback
	//and it will act as a pressable surface in your GUI
	class Button : public RenderableComponent {
	public:
		Button(int x, int y, int w, int h, TextureResource* tex, std::function<void()> onClick);

		EVENT_HANDLER(Click, {
			if (event->target != this) { return true; }
			//Call the callback function
			if (callback_) {
				callback_();
			}
			return true;
		});
		EVENT_HANDLER(Hover, {
			if (event->target != this) { return true; }

			state_ = sge::PackedTextureType::HOVER;
			unpackByStaticCasting(state_);
			return true;
		});
		EVENT_HANDLER(HoverLost, {
			if (event->target != this) { return true; }

			state_ = sge::PackedTextureType::NORMAL;
			unpackByStaticCasting(state_);
			return true;
		});
		EVENT_HANDLER(MouseDown, {
			if (event->target != this) { return true; }

			state_ = sge::PackedTextureType::CLICK;
			unpackByStaticCasting(state_);
			return true;
		});
		EVENT_HANDLER(MouseUp, {
			if (event->target != this) { return true; }

			state_ = sge::PackedTextureType::NORMAL;
			unpackByStaticCasting(state_);
		});

	private:
		void unpackByStaticCasting(sge::PackedTextureType t) {
			setUvBounds(static_cast<sge::PackedTexture*>(rsc_->get())->unpackTexture(t));
		}

		std::function<void()> callback_;
		sge::PackedTextureType state_ = sge::PackedTextureType::NORMAL;
	};
}