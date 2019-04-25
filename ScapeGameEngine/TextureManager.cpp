#include "TextureManager.h"

namespace sge {
	const char* defaultTextureFilename = ".\\textures\\default.png";
	Texture* TextureManager::boundTexture = nullptr;
	Texture* TextureManager::defaultTexture = nullptr;

	void TextureManager::init() {
		//Load the default checkerboard texture
		defaultTexture = new Texture(defaultTextureFilename);
		//No matching delete - the texture is used throughout
		//the whole runtime

		glActiveTexture(GL_TEXTURE0);
	}

	void TextureManager::bindTexture(Texture* tex) {
		if (tex != nullptr && boundTexture != tex) {
			glBindTexture(GL_TEXTURE_2D, tex->handle());
			boundTexture = tex;
		}
		else if (tex == nullptr && boundTexture != defaultTexture) {
			//If no texture is given, just bind the default one
			glBindTexture(GL_TEXTURE_2D, defaultTexture->handle());
			boundTexture = defaultTexture;
		}
	}
}