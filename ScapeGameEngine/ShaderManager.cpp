#include "ShaderManager.h"

namespace sge {
	ShaderProgram* ShaderManager::boundShader_ = nullptr;

	void ShaderManager::setActive(ShaderProgram& sh) {
		if (!(boundShader_) || (boundShader_->handle() != sh.handle())) {
			boundShader_ = &sh;
			glUseProgram(boundShader_->handle());
		}
	}

	const char* MVP_uniform = "MVP";

	void ShaderManager::bindMVP(glm::mat4x4 MVP) {
		GLint MVP_uniform_location = glGetUniformLocation(boundShader_->handle(), MVP_uniform);
		if (MVP_uniform_location < 0) {
			throw std::runtime_error("Can't find MVP uniform location! Shaders be da real MVP.");
		}

		glUniformMatrix4fv(MVP_uniform_location, 1, GL_FALSE, &MVP[0][0]);
	}
}