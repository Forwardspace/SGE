#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Shader.h"

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
	void makeShaders();
	void genPolygons();

	Renderable rectFromTwoPoints(Point2D bl, Point2D ur);

	extern GLFWwindow* wind;
	extern int w, h;
	extern Style::Enum style;
	extern std::map<int, sge::Texture*> textures;
}