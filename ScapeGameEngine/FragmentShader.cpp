#include "FragmentShader.h"

namespace sge {
	FragmentShader::FragmentShader() {
	}

	FragmentShader::FragmentShader(std::string filename) {
		shaderFromFile(GL_FRAGMENT_SHADER, filename);
	}

	FragmentShader::~FragmentShader() {
	}
}