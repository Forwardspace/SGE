#include "Shader.h"

namespace sge {
	Shader::Shader() {
	}

	void Shader::shaderFromFile(GLenum type, std::string filename) {
		const char* source = IOManager::stringFromFile(filename).c_str();

		GLint result = GL_FALSE;
		int loglength = 0;

		handle = glCreateShader(type);
		glShaderSource(handle, 1, &source, NULL);
		glCompileShader(handle);

		//Do some error checking
		glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &loglength);
		if (loglength > 0) {
			std::string log(loglength + 1, 0);
			glGetShaderInfoLog(handle, loglength, NULL, (char*)(log.data()));

			throw std::runtime_error(log);
			//No pun or joke here; I don't actually know what
			//the error is going to be.
		}
		//All done
	}

	Shader::~Shader() {
	}
}