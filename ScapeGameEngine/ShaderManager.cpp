#include "ShaderManager.h"

namespace sge {
	ShaderProgram* ShaderManager::boundShader_ = nullptr;

	void ShaderManager::setActive(ShaderProgram& sh) {
		if (!(boundShader_) || (boundShader_->handle() != sh.handle())) {
			boundShader_ = &sh;
			glUseProgram(boundShader_->handle());
		}
	}

	char* Sampler_uniform = (char*)"DefSampler";

	void ShaderManager::bindTexSampler(std::string name, GLuint absoluteUnit, Texture& tex, GLenum target) {
		//First find the uniform
		GLint Sampler_uniform_location = glGetUniformLocation(boundShader_->handle(), name.c_str());
		if (Sampler_uniform_location < 0) {
			throw std::runtime_error("Can't find Sampler uniform location! Sample this!");
		}

		//Configure the texture to use slot absoluteUnit
		glUniform1i(Sampler_uniform_location, absoluteUnit);

		//Now bind the texture to absoluteUnit
		glActiveTexture(GL_TEXTURE0 + absoluteUnit);
		glBindTexture(target, tex.handle());
	}
}