#pragma once
#include "stdheaders.h"

#ifndef SGE_TEXTURE_COLOUR_FORMAT
#define SGE_TEXTURE_COLOUR_FORMAT GL_BGRA
#endif

namespace sge {
	class Texture {
	public:
		Texture();
		~Texture();
		//Load from file
		Texture(std::string filename);

		GLuint handle() { return handle_; }

	private:
		void makeTexture(GLubyte* data);

		GLuint handle_ = NULL;
		int w_, h_;
	};
}
