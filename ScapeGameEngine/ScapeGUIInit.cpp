#include "ScapeGUIInit.h"
#include "TextureManager.h"

namespace sgeui {
	void initSGEUI(GLFWwindow* wind_, int w_, int h_, Style::Enum style_ = Style::GRAYISH_BLUE) {
		wind = wind_;
		w = w_;
		h = h_;
		style = style_;

		makeUIBase();
	}

	void makeUIBase() {
		genTextures();
		makeShaders();
		setVertexPtrs();
	}

	//Fills the texture tex with count pixels of col
	void fillTex(GLubyte* tex, int count, TexCol col) {
		GLuint size = sizeof(TexCol) * count;

		for (GLuint i = 0; i < size;) {
#if SGE_TEXTURE_COLOUR_FORMAT == GL_RGBA
			tex[i + 0] = col.r;
			tex[i + 1] = col.g;
			tex[i + 2] = col.b;
#elif SGE_TEXTURE_COLOUR_FORMAT == GL_BGRA
			tex[i + 0] = col.b;
			tex[i + 1] = col.g;
			tex[i + 2] = col.r;
#endif
			tex[i + 3] = col.a;
			i += 4;
		}
	}

	//Default SGEUI theme colours
#define SGEUI_BANNER_COL { (GLbyte)120, (GLbyte)120, (GLbyte)120, (GLbyte)255 }
#define SGEUI_BACK_COL_BLACK { (GLbyte)20, (GLbyte)20, (GLbyte)20, (GLbyte)255 }
#define SGEUI_BACK_COL_WHITE { (GLbyte)180, (GLbyte)180, (GLbyte)180, (GLbyte)255 }
#define SGEUI_BACK_COL_GRAYISH_BLUE { (GLbyte)55, (GLbyte)55, (GLbyte)70, (GLbyte)255 }

	void genTextures() {
		TexCol backCol;
		TexCol bannerCol = SGEUI_BANNER_COL;

		switch (style) {
		case Style::BLACK:
			backCol = SGEUI_BACK_COL_BLACK;
			break;
		case Style::WHITE:
			backCol = SGEUI_BACK_COL_WHITE;
			break;
		case Style::GRAYISH_BLUE:
			backCol = SGEUI_BACK_COL_GRAYISH_BLUE;
			break;
		}

		//DEBUG ONLY
		//Just set the default texture until
		//I can set up texture generation
		textures[TextureType::BACKGROUND] = sge::TextureManager::defaultTexture;
		//END DEBUG ONLY
	}

	void terminate() {
		for (auto pair : textures) {
			//Ignore the key, delete the value
			delete pair.second;
		}
	}

	//Default vertex shader
	const char* vsSrc =
		"#version 410 core										\n"
		"layout(location = 0) in vec2 pos;						\n"
		"layout(location = 1) in vec2 UV;						\n"
		"uniform mat4 translate;								\n"
		"out vec2 interUV;										\n"
		"														\n"
		"void main() {											\n"
		"	interUV = UV;										\n"
		"	gl_Position = translate * vec4(pos, 0, 1);			\n"
		"}														\n";
	//Default fragment shader
	const char* fsSrc =
		"#version 410 core						\n"
		 "uniform sampler2D DefSampler;			\n"
		 "in vec2 interUV;						\n"
		 "										\n"
		 "out vec4 col;							\n"
		 "void main() {							\n"
		 "	col = texture(DefSampler, interUV);	\n"
		 "}										\n";

	void makeShaders() {
		sge::VertexShader vsSh((std::string)vsSrc);
		sge::FragmentShader fsSh((std::string)fsSrc);

		sge::ShaderProgram sh({ vsSh, fsSh });
		GUIShaderProgram = sh;
	}

	void setVertexPtrs() {
		//Just configure the VBO to accept 2D coordinates (instead of 3D)
		glBindBuffer(GL_ARRAY_BUFFER, sge::BufferManager::VBO(sge::VBOType::VERTEX2D));
		glVertexAttribPointer(0, 2 /* <- The important part */, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	GLFWwindow* wind;
	int w, h;
	Style::Enum style;
	std::map<int, sge::Texture*> textures;
	sge::ShaderProgram GUIShaderProgram;
}