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

	/*namespace TextureType {
		enum Enum {
			THEME,
			NORMAL,
			PACKED,
		};
	}*/

	void initSGEUI(GLFWwindow* wind_, int w_, int h_);
	void makeUIBase();
	void loadResources();
	void makeShaders();
	void setVertexPtrs();

	extern GLFWwindow* wind;
	extern int windW, windH;

	extern std::map<int, sge::Texture*> textures;
	extern std::map<int, sge::PackedTexture*> packedTextures;
	extern int defaultTheme;
	
	extern sge::ShaderProgram GUIShaderProgram;
}