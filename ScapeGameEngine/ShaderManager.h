#pragma once
#include "stdheaders.h"
#include "ShaderProgram.h"

namespace sge {
	class ShaderManager {
	public:
		ShaderManager() = delete; //Singleton
		~ShaderManager() = delete; //Singleton

		//Called internally
		static void setActive(ShaderProgram& sh);
		//Binds the MVP uniform to the bound shader
		static void bindMVP(glm::mat4x4 MVP);
	
	private:
		static ShaderProgram* boundShader_;
	};
}