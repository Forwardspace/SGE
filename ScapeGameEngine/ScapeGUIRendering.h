#pragma once
#include "ScapeGUITypes.h"
#include "ScapeGUIComponent.h"

namespace sgeui {
	class Renderer {
	public:
		void renderQuad(RedrawEvent re, RenderableComponent* comp);
	};
}