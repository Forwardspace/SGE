#include "Texture.h"

namespace sge {
	Texture::Texture() {
	}

	Texture::~Texture() {
	}

	Texture::Texture(std::string filename) {
		ILuint image;
		ilGenImages(1, &image);
		ilBindImage(image);

		try {
			ILboolean success = ilLoadImage(filename.c_str());

			auto error = iluErrorString(ilGetError());

			if (!success) {
				throw std::runtime_error("Texture error: Unable to ilLoadImage().");
			}

			//Make the image compatible with OpenGL
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

			if (!success) {
				throw std::runtime_error("Texture error: Unable to ilConvertImage().");
			}

			//All done, now extract the raw data from it
			ILubyte* dataPtr = ilGetData();
			
			if (dataPtr == nullptr) {
				throw std::runtime_error("Texture error: null pointer");
			}

			w_ = ilGetInteger(IL_IMAGE_WIDTH);
			h_ = ilGetInteger(IL_IMAGE_HEIGHT);

			//(Is it RGB or BGR?)
			GLenum format = ilGetInteger(IL_IMAGE_FORMAT);

			//Finally, create the texture
			makeTexture((GLubyte*)dataPtr, format);

			ilDeleteImages(1, &image);
		}
		catch (std::runtime_error err) {
			throw std::runtime_error(
				"Unable to load texture. This texture lacks texture... (" + 
				std::string(err.what()) +
				")"
			);
		}
	}

	//Format must be either GL_RGB or GL_BGR
	Texture::Texture(GLubyte* data, int w, int h, GLenum format) {
		w_ = w;
		h_ = h;
		makeTexture(data, format);
	}

	void Texture::makeTexture(GLubyte* data, GLenum format) {
		glGenTextures(1, &handle_);
		glBindTexture(GL_TEXTURE_2D, handle_);

		//Give the data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w_, h_, 0, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Use mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
		//Generate those mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}