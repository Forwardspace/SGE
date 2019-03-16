#include "VertexShader.h"

namespace sge {
	VertexShader::VertexShader() {
	}

	VertexShader::VertexShader(std::string filename) {
		shaderFromFile(GL_VERTEX_SHADER, filename);
	}

	VertexShader::~VertexShader() {
	}
}