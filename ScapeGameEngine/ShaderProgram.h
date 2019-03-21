#pragma once
#include "stdheaders.h"
#include "Shader.h"

namespace sge {
	class ShaderProgram {
	public:
		ShaderProgram();
		ShaderProgram(std::initializer_list<Shader> shaders);
		~ShaderProgram();

		GLuint handle() { return handle_; }

	private:
		GLuint handle_ = NULL;
	};
}