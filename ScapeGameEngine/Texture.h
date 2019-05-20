#pragma once
#include "stdheaders.h"

namespace sge {
	class Texture {
	public:
		Texture();
		~Texture();
		//Load from file
		Texture(fs::path filename);
		//Load from array
		Texture(GLubyte* data, int w, int h, GLenum format);

		GLuint handle() { return handle_; }

	private:
		void makeTexture(GLubyte* data, GLenum format);

		GLuint handle_ = NULL;
		int w_, h_;
	};
}
