#include "Shader.h"

namespace sge {
	Shader::Shader() {
	}

	void Shader::shaderFromFile(GLenum type, std::string filename) {
		std::string shaderfile = IOManager::stringFromFile(filename).c_str();
		const char* source = shaderfile.c_str();

		GLint result = GL_FALSE;
		int loglength = 0;

		handle_ = glCreateShader(type);
		glShaderSource(handle_, 1, &source, NULL);
		glCompileShader(handle_);

		//Do some error checking
		glGetShaderiv(handle_, GL_COMPILE_STATUS, &result);
		glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &loglength);
		if (loglength > 0) {
			std::string log(loglength + 1, 0);
			glGetShaderInfoLog(handle_, loglength, NULL, (char*)(log.data()));

			throw std::runtime_error(log);
			//No pun or joke here; I don't actually know what
			//the error is going to be.
		}
		//All done
	}

	Shader::~Shader() {
	}
}