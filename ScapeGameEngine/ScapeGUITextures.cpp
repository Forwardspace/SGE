#include "ScapeGUITextures.h"

namespace sgeui {
	std::vector<sgeui::TextureResource*> TextureManager::globalTextures_;
	std::vector<int> TextureManager::globalThemeIndices_;

	TextureResource* TextureManager::get(std::string name) {
		for (auto rsc : globalTextures_) {
			if (rsc->name() == name) {
				return rsc;
			}
		}

		return nullptr;
	}

	ThemeTextureResource* TextureManager::getTheme(std::string name) {
		for (auto i : globalThemeIndices_) {
			if (globalTextures_[i]->name() == name) {
				return static_cast<ThemeTextureResource*>(globalTextures_[i]);
			}
		}

		return nullptr;
	}

	void TextureManager::terminate() {
		for (auto tex : globalTextures_) {
			delete tex;
		}
	}
}