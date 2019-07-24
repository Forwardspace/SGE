#include "stdheaders.h"

#include "ScapeGUITypes.h"

namespace sgeui {
	class TextureManager {
	public:
		static inline void add(sgeui::TextureResource* rsc) { globalTextures_.push_back(rsc); }
		static inline void add(sgeui::ThemeTextureResource* rsc) 
			{ globalThemeIndices_.push_back(globalTextures_.size()); globalTextures_.push_back(rsc); }
		static inline void remove(int index) { globalTextures_.erase(globalTextures_.begin() + index); }

		static inline sgeui::TextureResource* get(int index) { return globalTextures_[index]; }

		static sgeui::TextureResource* get(std::string name);
		static sgeui::ThemeTextureResource* getTheme()

		static void terminate();
	private:
		static std::vector<sgeui::TextureResource*> globalTextures_;
		static std::vector<int> globalThemeIndices_;
	};
}