#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "IOManager.h"

namespace sge {
	class TextureManager {
	public:
		static void bindTexture(Texture* tex);

		static void init();
		static void terminate();

		TextureManager() = delete;	//Singleton
		~TextureManager() = delete;

		static Texture* defaultTexture;
	private:
		static Texture* boundTexture;
	};
}