#include "BufferManager.h"

namespace sge {
	GLuint BufferManager::VAO(VAOType type) {
		if (VAOs_[type] == NULL) {
			//No VAO bound, make one
			GLuint VAO = NULL;
			glGenVertexArrays(1, &VAO);

			if (VAO == NULL) {
				throw std::runtime_error("Unable to generate a new VAO! Confusing OpenGL is confusing.");
			}

			//Set it as a default for the type given
			VAOs_[type] = VAO;
		}
		else {
			return VAOs_[type];
		}
	}

	GLuint BufferManager::VBO() {
		if (VBO_ == NULL) {
			//No VBO found, make one
			GLuint newVBO = NULL;
			glGenBuffers(1, &newVBO);

			if (newVBO == NULL) {
				throw std::runtime_error("Unable to generate a new VBO! Buffering...");
			}

			//Set it as a default
			VBO_ = newVBO;
		}

		return VBO_;
	}

	GLuint BufferManager::EAB() {
		if (EAB_ == NULL) {
			//No EAB found, make one
			GLuint newEAB = NULL;
			glGenBuffers(1, &newEAB);

			if (newEAB == NULL) {
				throw std::runtime_error("Unable to generate a new EAB! array deelementalisation in progress...");
			}
		
			EAB_ = newEAB;
		}

		return EAB_;
	}

	BufferManager::BufferManager() {
		EAB_ = NULL;
		VBO_ = NULL;
	}
}