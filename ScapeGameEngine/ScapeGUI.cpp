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
		genPolygons();
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

	void genTextures() {
		TexCol backCol;
		TexCol bannerCol = {120, 120, 120, 255 };

		switch (style) {
		case Style::BLACK:
			backCol = { 20, 20, 20, 255 };
			break;
		case Style::WHITE:
			backCol = { 180, 180, 180, 255 };
			break;
		case Style::GRAYISH_BLUE:
			backCol = { 55, 55, 70, 255 };
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

	void genPolygons() {

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

	Style::Enum style;

	std::map<int, sge::Texture*> textures;
}