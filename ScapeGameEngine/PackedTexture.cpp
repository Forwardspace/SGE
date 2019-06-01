#include "PackedTexture.h"

namespace sge {
	PackedTexture::PackedTexture() {
	}

	PackedTexture::PackedTexture(fs::path path) {
		//Load the whole sprite sheet
		loadFromFile(path);

		//Load the accompanying csv file
		fs::path csvPath = path.parent_path() / (path.stem().string() + ".csv");
		auto vec = IOManager::stringVecFromCSV(csvPath);

		//Parse it to convert to Enum
		for (auto& texType : vec) {
			if (texType == "NORMAL") {
				types.push_back(PackedTextureType::Enum::NORMAL);
			}
			else if (texType == "HOVER") {
				types.push_back(PackedTextureType::Enum::HOVER);
			}
			else if (texType == "CLICK") {
				types.push_back(PackedTextureType::Enum::CLICK);
			}
			else if (texType == "DISABLED") {
				types.push_back(PackedTextureType::Enum::DISABLED);
			}
			else {
				throw std::runtime_error("Error: undefined CSV value encountered! Don't mess with CSVs!");
			}
		}
	}

	PackedTexture::~PackedTexture() {
	}

	std::array<glm::vec2, 2> PackedTexture::unpackTexture(PackedTextureType::Enum type) {
		int index = -1;
		//First search the types vector for the first of type
		for (int i = 0; i < types.size(); i++) {
			if (types[i] == type) {
				//Match!
				index = i;
				break;
			}
		}
		if (index == -1) {
			//Soft error - we can continue; although the GUI may look wrong
			//Return the first texture
			index = 0;

			//DEBUG ONLY
			assert(false);
		}

		//Calculate the UVs based on the num. of textures and index
		glm::vec2 bl = { (float)index / types.size(), 0 };
		glm::vec2 ur = { (float)1 / types.size() + bl.x, 1 };
		
		return {bl, ur};
	}

	std::array<glm::vec2, 4> quadUVsFromTwoPoints(glm::vec2 bl, glm::vec2 ur) {
		return { bl, ur, { bl.x, ur.y }, { ur.x, bl.y } };
	}
}