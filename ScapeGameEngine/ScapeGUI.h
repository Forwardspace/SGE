#pragma once
#include "stdheaders.h"
#include "Texture.h"

#include "ScapeGUIRendering.h"

namespace sgeui {
	namespace Style {
		enum Enum {
			BLACK,
			WHITE,
			GRAYISH_BLUE
		};
	}

	namespace TextureType {
		enum Enum {
			BACKGROUND
		};
	}

	void init(GLFWwindow* wind_, int w_, int h_, Style::Enum style_);
	void makeUIBase();
	void genTextures();
	void genPolygons();

	Renderable rectFromTwoPoints();

	GLFWwindow* wind;
	int w, h;
}