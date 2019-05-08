#include "FragmentShader.h"

namespace sge {
	FragmentShader::FragmentShader() {
	}

	FragmentShader::FragmentShader(fs::path filename) {
		std::string source = IOManager::stringFromFile(filename);
		shaderFromString(GL_FRAGMENT_SHADER, source);
	}

	FragmentShader::FragmentShader(std::string source) {
		shaderFromString(GL_FRAGMENT_SHADER, source);
	}

	FragmentShader::~FragmentShader() {
	}
}