#include "Material.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace sge {
	extern ShaderProgram* staticShader;

	Material::Material() {
		//Add the default checkerboard texture as a diffuse texture
		addFromListUnchecked({ {TextureManager::defaultTexture, "diffuse"} });
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

	Material::Material(ShaderProgram* shader, std::initializer_list<std::pair<Texture*, std::string>>& textures, bool skipCheck) {
		shader_ = shader;
		shaderSpecified = true;

		if (skipCheck) {
			addFromListUnchecked(textures);
		}
		else {
			addFromListChecked(textures);
		}
	}

	Material::Material(std::initializer_list<std::pair<Texture*, std::string>>& textures, bool skipCheck) {
		if (skipCheck) {
			addFromListUnchecked(textures);
		}
		else {
			addFromListChecked(textures);
		}
	}

	Material::Material(std::vector<std::pair<Texture*, std::string>>& textures, bool skipCheck) {
		if (skipCheck) {
			addFromVecUnchecked(textures);
		}
		else {
			addFromVecChecked(textures);
		}
	}

	void Material::addFromVecChecked(std::vector<std::pair<Texture*, std::string>>& textures) {
		for (auto& pair : textures) {
			//Check if the texture name is in names (if it is valid)
			int i = 0;
			for (auto name : textureNameTypes) {
				if (pair.second == name) {
					//It is
					textures_[i] = pair.first;

					//If the texture type name matches any entry in 
					//textureTypeNames, there is, of course, no need
					//to throw a runtime error
					goto skipThrow;
				}

				i++;
			}

			//Nope; the name is unsupported
			throw std::runtime_error("Error: texture name in Material is invalid!");

		skipThrow:
			continue;
		}
	}

	void Material::addFromVecUnchecked(std::vector<std::pair<Texture*, std::string>>& textures) {
		if (textures.size() > textureNameTypes.size()) {
			throw std::runtime_error("Error: too many textures to addFromVecUnchecked()!");
		}

		for (int i = 0; i < textures.size(); i++) {
			if (textures[i].second == textureNameTypes[i]) {
				textures_[i] = textures[i].first;
			}
		}
	}

	void Material::addFromListChecked(std::initializer_list<std::pair<Texture*, std::string>> textures) {
		addFromVecChecked(std::vector<std::pair<Texture*, std::string>>(textures.begin(), textures.end()));
	}

	void Material::addFromListUnchecked(std::initializer_list<std::pair<Texture*, std::string>> textures) {
		addFromVecUnchecked(std::vector<std::pair<Texture*, std::string>>(textures.begin(), textures.end()));
	}

	Material defaultMaterial;
}
