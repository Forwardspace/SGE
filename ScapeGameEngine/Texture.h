#pragma once
#include "stdheaders.h"

namespace sge {
	class Texture {
	public:
		Texture();
		virtual ~Texture();
		//Load from file
		Texture(fs::path filename);
		//Load from array
		Texture(GLubyte* data, int w, int h, GLenum format);

		GLuint handle() { return handle_; }

	protected:
		void makeTexture(GLubyte* data, GLenum format);
		void loadFromFile(fs::path filename);

		GLuint handle_ = NULL;
		int w_, h_;
	};
}
