#include "Shader.h"

namespace sge {
	Shader::Shader() {
	}

	void Shader::shaderFromString(GLenum type, std::string source) {
		GLint result = GL_FALSE;
		int loglength = 0;

		const char* data = source.c_str();

		handle_ = glCreateShader(type);
		glShaderSource(handle_, 1, &data, NULL);
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

	Shader::Shader(fs::path filename) {
		//Unable to create shader without a type
		//std::string source = IOManager::stringFromFile(filename);
		//shaderFromString(<TYPE>, source);
	}

	Shader::Shader(std::string data) {
		//Unable to create shader without a type
		//shaderFromString(<TYPE>, data);
	}

	Shader::~Shader() {
	}
}