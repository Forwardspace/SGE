#include "Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace sge {
	extern ShaderProgram* staticShader;

	Material::Material() {
		//Add the default checkerboard texture as a diffuse texture
		addTextures({ {TextureManager::defaultTexture, "diffuse"} });
	}

	void Material::activate() {
		//Bind the required shader
		if (shader_) {
			ShaderManager::setActive(*shader_);
		}

		//Now bind the textures according to the order in textureNameTypes
		for (int i = 0; i < MAX_TEXTURES; i++) {
			if (textures_[i]) {
				//The texture exists, try to bind it to the sampler number i
				ShaderManager::bindTexSampler(textureNameTypes[i], i, *textures_[i]);
			}
		}
	}

	Material::Material(ShaderProgram* shader, std::initializer_list<std::pair<Texture*, std::string>> textures) {
		shader_ = shader;
		shaderSpecified = true;

		addTextures(textures);
	}

	Material::Material(std::initializer_list<std::pair<Texture*, std::string>> textures) {
		addTextures(textures);
	}

	void Material::addTextures(std::initializer_list<std::pair<Texture*, std::string>> textures) {
		for (auto& pair : textures) {
			//Check if the texture name is in names (if it is valid)
			int i = 0;
			for (auto name : textureNameTypes) {
				if (std::get<1>(pair) == name) {
					//It is
					textures_[i] = std::get<0>(pair);

					//If the texture type name matches any entry in 
					//textureTypeNames, there is, of course, no need
					//to throw a runtime error, therefore continue
					//with the outer loop
					goto skip_throw;
				}

				i++;
			}

			//Nope; the name is unsupported
			throw std::runtime_error("Error: texture name in Material is invalid!");

		skip_throw:
			continue;
		}
	}

	Material defaultMaterial;
}
