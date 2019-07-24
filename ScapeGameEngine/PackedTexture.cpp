#include "PackedTexture.h"

namespace sge {
	PackedTexture::PackedTexture() {
	}

	PackedTexture::PackedTexture(fs::path path) {
		//Load the whole sprite sheet
		loadFromFile(path);

		//Load the accompanying csv file
		fs::path csvPath = path.parent_path() / (path.stem().string() + ".csv");
		auto xml = ParsedXML(csvPath);

		auto root = xml.findNode("textureTypes");
		if (!root) {
			//Not correctly formated xml document
			throw std::runtime_error("Incorrectly formatted XML document. Fix ur docs.");
		}

		//Translate all types in the XML document
		//into PackedTextureType::Enum values
		auto currentType = root->first_node("type");
		while (currentType) {
			std::string type = currentType->value();

			if (type == "NORMAL") {
				types.push_back(PackedTextureType::Enum::NORMAL);
			}
			else if (type == "HOVER") {
				types.push_back(PackedTextureType::Enum::HOVER);
			}
			else if (type == "CLICK") {
				types.push_back(PackedTextureType::Enum::CLICK);
			}
			else if (type == "DISABLED") {
				types.push_back(PackedTextureType::Enum::DISABLED);
			}
			else {
				throw std::runtime_error("Error: undefined XML value encountered! Don't mess with XMLs!");
			}

			currentType = currentType->next_sibling("type");
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
		}

		//Calculate the UVs based on the num. of textures and index
		glm::vec2 bl = { (float)index / types.size(), 0 };
		glm::vec2 ur = { (float)1 / types.size() + bl.x, 1 };
		
		return {bl, ur};
	}
}