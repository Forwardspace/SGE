#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "PackedTexture.h"

#include "ScapeGUITypes.h"

namespace sgeui {
	namespace Style {
		enum Enum {
			BLACK,
			WHITE,
			GRAYISH_BLUE
		};
	}

	void initSGEUI(GLFWwindow* wind_, int w_, int h_);
	void loadResources();
	void makeShaders();

	void setVertexPtrs();
	void updateMouseDelta();

	extern int mouseDeltaX, mouseDeltaY;

	extern GLFWwindow* wind;
	extern int windW, windH;

	extern Theme* defaultTheme;
	
	extern sge::ShaderProgram* GUIShaderProgram;
}