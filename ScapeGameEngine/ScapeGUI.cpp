#include "ScapeGUI.h"

namespace sgeui {
	void init(GLFWwindow* wind_, int w_, int h_, Style::Enum style_ = Style::GRAYISH_BLUE) {
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
		
		//Generate the world's smallest default background texture
		const int backTexSize = 2 * 2 * sizeof(TexCol); //Yes, a 2 by 2 texture!
		GLubyte backTexData[backTexSize];
		//Start at pixel 0
		fillTex(backTexData, 2, bannerCol);
		//Start at pixel 3
		fillTex(&backTexData[2], 2, backCol);

		sge::Texture* backTex = new sge::Texture();
		textures[TextureType::BACKGROUND] = backTex;
	}

	void terminate() {
		for (auto pair : textures) {
			//Ignore the key, delete the value
			delete pair.second;
		}
	}

	//Default vertex shader
	const char* vsSrc =
		"#version 410 core					\
		 layout(location = 0) in vec2 pos;	\
		 uniform mat3 translate;			\
											\
		 void main() {						\
			gl_Position = translate * pos;	\
		 }									";
	//Default fragment shader
	const char* fsSrc = 
		"#version 410 core					\
		 layout(location = 0) in vec2 UV;	\
		 uniform sampler2d DefSampler;		\
											\
		 out vec4 col;						\
		 void main() {						\
			col = texture(DefSampler, UV);	\
		 }									";

	void makeShaders() {
		sge::Shader vsSh((std::string)vsSrc);
		sge::Shader fsSh((std::string)fsSrc);

		sge::ShaderProgram sh({vsSh, fsSh});
		GUIShaderProgram = sh;
	}

	void setVertexPtrs() {
		//Just configure the VBO to accept 2D coordinates (instead of 3D)
		glBindBuffer(GL_ARRAY_BUFFER, sge::BufferManager::VBO(sge::VBOType::VERTEX2D));
		glVertexAttribPointer(0, 2 /* <- The important part */, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	//Provided a bottom left and an upper right point,
	//this will generate a renderable rectangle bounded
	//by these points
	Renderable rectFromTwoPoints(Point2D bl, Point2D ur) {
		//Generate two triangles and all corresponding data
		PointArray pa = { { bl.x, bl.y }, { ur.x, ur.y }, { bl.x, ur.y }, { ur.x, bl.y } };
		IndexArray ia = { 0, 3, 2, 3, 1, 2 };
		UVArray ua = { { 0, 1 }, { 0, 1 }, { 0, 0 }, { 1, 1 } };

		Renderable rectangle(pa, ia, ua);
		return rectangle;
	}

	GLFWwindow* wind;
	int w, h;
	Style::Enum style;
	std::map<int, sge::Texture*> textures;
	sge::ShaderProgram GUIShaderProgram;
}