#pragma once
#include "Texture.h"
#include "ShaderProgram.h"

#define MAX_TEXTURES 8

namespace sge {
	//Describes how an object looks when rendering
	//Holds all required textures and an assigned shader

	//For now, there are 8 supported textures
	//these are their names (the uniform names in the shader must match)
	//The textures are bound to the first 8 texture slots in this order
	const std::array<const std::string, 8> textureNameTypes {
		"diffuse",
		"normal",
		"specular",
		"bump",
		"glow",
		"reflection",
		"opacity",
		"extra"
	};

	class Material {
	public:
		Material();
		Material(ShaderProgram* shader, std::initializer_list<std::pair<Texture*, std::string>> textures);
		Material(std::initializer_list<std::pair<Texture*, std::string>> textures);

		void activate();
		bool shaderValid() { return shader_ ? true : false; }

		bool shaderSpecified = false;

	private:
		ShaderProgram* shader_ = nullptr;
		std::array<Texture*, MAX_TEXTURES> textures_ = {0, 0, 0, 0, 0, 0, 0, 0};

		void addTextures(std::initializer_list<std::pair<Texture*, std::string>> textures);
	};

	extern Material defaultMaterial;
}
