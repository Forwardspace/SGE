#include "ShaderProgram.h"

namespace sge {
	ShaderProgram::ShaderProgram() {
	}

	ShaderProgram::ShaderProgram(std::initializer_list<Shader> shaders) {
		handle_ = glCreateProgram();

		for (auto shader : shaders) {
			glAttachShader(handle_, shader.handle());
		}

		glLinkProgram(handle_);

		//Error checking
		GLint result = GL_FALSE;
		int loglength = 0;

		glGetProgramiv(handle_, GL_LINK_STATUS, &result);
		glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &loglength);
		if (loglength > 0) {
			std::string log(loglength + 1, 0);
			glGetShaderInfoLog(handle_, loglength, NULL, (char*)(log.data()));

			throw std::runtime_error(log);
		}

		//Debugging only - remove when shader management is implemented
		glUseProgram(handle_);
	}

	ShaderProgram::~ShaderProgram() {
	}
}