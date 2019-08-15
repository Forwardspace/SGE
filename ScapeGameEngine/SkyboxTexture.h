#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "ShaderProgram.h"

namespace sge {
	extern ShaderProgram* skyboxShader;

	class SkyboxTexture : public Texture {
	public:
		SkyboxTexture(fs::path filename);

		void activate();

	private:
		//Yes, this texture has a render function
		//No, it's not really an object - it does not have
		//a model matrix nor materials.
		//VPmat = projection * view matrices
		void render(glm::mat4 VPmat);
		void initVAO();

		friend class Renderer;
	};
}
