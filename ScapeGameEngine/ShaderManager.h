#pragma once
#include "stdheaders.h"
#include "ShaderProgram.h"

namespace sge {
	class ShaderManager {
	public:
		ShaderManager() = delete; //Singleton
		~ShaderManager() = delete;

		//Called internally
		static void setActive(ShaderProgram& sh);
		static void pushActive(ShaderProgram& newActive);
		static void popActive();
		//Binds the MVP uniform to the bound shader
		static void bindMVP(glm::mat4x4 MVP);

		static void bindSamplerTexUnit(int absoluteUnit);
	
	private:
		static ShaderProgram* boundShader_;
		static std::stack<ShaderProgram*> shaderStack;
	};
}