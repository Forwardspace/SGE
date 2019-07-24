#pragma once
#include "ScapeGUITypes.h"
#include "ScapeGUIComponent.h"

#include "ScapeGUIInit.h"

namespace sgeui {
	class Renderer {
	public:
		void renderQuad(RedrawEvent re, RenderableComponent* comp);
	};
}