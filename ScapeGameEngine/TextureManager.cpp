#include "TextureManager.h"

namespace sge {
	const char* defaultTextureFilename = ".\\textures\\default.png";
	Texture* TextureManager::boundTexture = nullptr;
	Texture* TextureManager::defaultTexture = nullptr;

	void TextureManager::init() {
		//Load the default checkerboard texture
		defaultTexture = new Texture(defaultTextureFilename);

		//Create the default material
		defaultMaterial = Material();
	}

	void TextureManager::terminate() {
		delete defaultTexture;
	}
}