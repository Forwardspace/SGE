#include "VertexShader.h"

namespace sge {
	VertexShader::VertexShader() {
	}

	VertexShader::VertexShader(fs::path filename) {
		std::string source = IOManager::stringFromFile(filename);
		shaderFromString(GL_VERTEX_SHADER, source);
	}

	VertexShader::VertexShader(std::string source) {
		shaderFromString(GL_VERTEX_SHADER, source);
	}

	VertexShader::~VertexShader() {
	}
}