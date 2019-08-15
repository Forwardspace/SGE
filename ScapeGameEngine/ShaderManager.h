#pragma once

#include "stdheaders.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace sge {
	class ShaderManager {
	public:
		ShaderManager() = delete; //Singleton
		~ShaderManager() = delete;

		//Called internally
		static void setActive(ShaderProgram& sh);
		//Binds a uniform named "name" of value "value "
		//to the bound shader
		//If the uniform could not be found, returns false
		template <typename T>
		static bool bindUniform(std::string name, T& value);

		//Textures are bound to a slot, which is in turn bound to a uniform sampler
		//Bind the texture at specified slot
		static void bindTexSampler(std::string name, GLuint absoluteUnit, Texture& tex, GLenum target = GL_TEXTURE_2D);
	
	private:
		static ShaderProgram* boundShader_;

		friend GLint getUniformLoc(std::string name);
	};
}

#include "shadermanagerimpl.h"