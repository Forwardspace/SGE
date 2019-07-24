#pragma once
#include "ScapeGUITextures.h"

namespace sgeui {
	std::vector<sgeui::TextureResource*> globalTextures_;
	std::vector<int> globalThemeIndices_;

	void TextureManager::terminate() {
		for (auto tex : globalTextures_) {
			delete tex;
		}
	}
}