#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderManager.h"
#include "BufferManager.h"

#include "ScapeGUITypes.h"

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
			BACKGROUND,
			CLOSE_BUTTON
		};
	}

	void initSGEUI(GLFWwindow* wind_, int w_, int h_, Style::Enum style_);
	void makeUIBase();
	void genTextures();
	void makeShaders();
	void setVertexPtrs();

	extern GLFWwindow* wind;
	extern int windW, windH;
	extern Style::Enum style;
	extern std::map<int, sge::Texture*> textures;
	extern sge::ShaderProgram GUIShaderProgram;
}