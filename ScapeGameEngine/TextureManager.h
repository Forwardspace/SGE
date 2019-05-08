#pragma once
#include "stdheaders.h"
#include "Texture.h"

namespace sge {
	class TextureManager {
	public:
		static void bindTexture(Texture* tex);

		static void init();
		static void terminate();

		TextureManager() = delete;	//Singleton
		~TextureManager() = delete;
	private:
		static Texture* boundTexture;
		static Texture* defaultTexture;
	};
}