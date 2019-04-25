#include "ShaderManager.h"

namespace sge {
	ShaderProgram* ShaderManager::boundShader_ = nullptr;

	void ShaderManager::setActive(ShaderProgram& sh) {
		if (!(boundShader_) || (boundShader_->handle() != sh.handle())) {
			boundShader_ = &sh;
			glUseProgram(boundShader_->handle());
		}
	}

	char* MVP_uniform = (char*)"MVP";

	void ShaderManager::bindMVP(glm::mat4x4 MVP) {
		GLint MVP_uniform_location = glGetUniformLocation(boundShader_->handle(), MVP_uniform);
		if (MVP_uniform_location < 0) {
			throw std::runtime_error("Can't find MVP uniform location! Shaders be da real MVP.");
		}

		glUniformMatrix4fv(MVP_uniform_location, 1, GL_FALSE, &MVP[0][0]);
	}

	char* Sampler_uniform = (char*)"DefSampler";

	void ShaderManager::bindSamplerTexUnit(int absoluteUnit) {
		GLint Sampler_uniform_location = glGetUniformLocation(boundShader_->handle(), Sampler_uniform);
		if (Sampler_uniform_location < 0) {
			throw std::runtime_error("Can't find Sampler uniform location! Sample this!");
		}

		glUniform1i(Sampler_uniform_location, absoluteUnit);
	}
}