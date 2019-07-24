#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "ParsedXML.h"

namespace sge {
	namespace PackedTextureType {
		enum Enum {
			NORMAL,
			HOVER,
			CLICK,
			DISABLED,
			RELEASED
		};
	}

	class PackedTexture : public Texture {
	public:
		PackedTexture();
		PackedTexture(fs::path path);
		~PackedTexture();

		//Provided with the type of the texture you want,
		//this returns { bl, ur } UV coords
		std::array<glm::vec2, 2> unpackTexture(PackedTextureType::Enum type);
	private:
		//An ordered list of stored textures
		std::vector<PackedTextureType::Enum> types;
	};
}