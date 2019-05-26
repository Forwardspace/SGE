#include "ScapeGUIInit.h"
#include "TextureManager.h"

namespace sgeui {
	void initSGEUI(GLFWwindow* wind_, int w_, int h_, Style::Enum style_ = Style::GRAYISH_BLUE) {
		wind = wind_;
		windW = w_;
		windH = h_;
		style = style_;

		makeUIBase();
	}

	void makeUIBase() {
		genTextures();
		makeShaders();
		setVertexPtrs();
	}

#define SGEUI_BLACK_BCK_FNAME "textures\\gui\\bck_black.png";
#define SGEUI_WHITE_BCK_FNAME "textures\\gui\\bck_white.png";
#define SGEUI_BLUISH_GRAY_BCK_FNAME "textures\\gui\\bck_bluish_gray.png";

	const std::string textureFilenames[] = {
		"textures\\gui\\close_button.png"
	};

	void genTextures() {
		//Create the background texture based on the style enum
		fs::path bckFilename = "error_filename";

		switch (style) {
		case Style::BLACK:
			bckFilename = SGEUI_BLACK_BCK_FNAME;
			break;
		case Style::WHITE:
			bckFilename = SGEUI_WHITE_BCK_FNAME;
			break;
		case Style::GRAYISH_BLUE:
			//YES, it's the same
			//NO, I won't change it
			bckFilename = SGEUI_BLUISH_GRAY_BCK_FNAME;
			break;
		}

		sge::Texture* backTex = new sge::Texture(bckFilename);
		textures[TextureType::BACKGROUND] = backTex;

		////Load the rest of the textures iteratively
		//for (int i = 0; i < sizeof(textureFilenames); i++) {
		//	sge::Texture* tex = new sge::Texture(textureFilenames[i]);
		//	textures[i + 1] = backTex;
		//}
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
	int windW, windH;
	Style::Enum style;
	std::map<int, sge::Texture*> textures;
	sge::ShaderProgram GUIShaderProgram;
}