#pragma once
#include "stdheaders.h"
#include "Material.h"
#include "IOManager.h"

namespace sge {
	class TextureManager {
	public:
		static void init();
		static void terminate();

		TextureManager() = delete;	//Singleton
		~TextureManager() = delete;

		static Texture* defaultTexture;
	private:
		static Texture* boundTexture;
	};
}