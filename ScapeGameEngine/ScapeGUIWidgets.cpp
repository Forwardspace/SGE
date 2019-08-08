#include "ScapeGUIWidgets.h"

namespace sgeui {
	Button::Button(int x, int y, int w, int h, TextureResource* tex, std::function<void()> onClick) :
	RenderableComponent(x, y, w, h, tex), callback_(onClick) {
		HANDLES_EVENT(Click);
		HANDLES_EVENT(Hover);
		HANDLES_EVENT(HoverLost);
		HANDLES_EVENT(MouseDown);
		HANDLES_EVENT(MouseUp);

		unpackByStaticCasting(state_);

		intDesc.isClickable = true;
		intDesc.isHoverable = true;
	}
}