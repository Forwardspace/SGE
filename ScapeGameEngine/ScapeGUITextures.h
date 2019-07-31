#pragma once
#include "stdheaders.h"

#include "ScapeGUITypes.h"

namespace sgeui {
	class TextureManager {
	public:
		//Singleton
		TextureManager() = delete;
		~TextureManager() = delete;

		static void add(sgeui::TextureResource* rsc) { globalTextures_.push_back(rsc); }
		static void add(sgeui::ThemeTextureResource* rsc) 
			{ globalThemeIndices_.push_back(globalTextures_.size()); globalTextures_.push_back(rsc); }
		static void remove(int index) { globalTextures_.erase(globalTextures_.begin() + index); }

		static sgeui::TextureResource* get(int index) { return globalTextures_[index]; }

		static sgeui::TextureResource* get(std::string name);
		static sgeui::ThemeTextureResource* getTheme(std::string name);

		static void terminate();
	private:
		static std::vector<sgeui::TextureResource*> globalTextures_;
		static std::vector<int> globalThemeIndices_;
	};
}