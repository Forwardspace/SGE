#include "BufferManager.h"

namespace sge {
	GLuint BufferManager::EAB_ = NULL;
	std::map<int, GLuint> BufferManager::VBOs_;
	std::map<int, GLuint> BufferManager::FBOs_;
	std::map<int, GLuint> BufferManager::VAOs_;

	GLuint BufferManager::VAO(VAOType::Enum type) {
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
		
		return VAOs_[type];
	}

	GLuint BufferManager::VBO(VBOType::Enum type) {
		if (VBOs_[type] == NULL) {
			//No VBO found, make one
			GLuint VBO = NULL;
			glGenBuffers(1, &VBO);

			if (VBO == NULL) {
				throw std::runtime_error("Unable to generate a new VBO! Buffering...");
			}

			//Set it as a default
			VBOs_[type] = VBO;
		}

		return VBOs_[type];
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

	GLuint BufferManager::FBO(FBOType::Enum type) {
		if (FBOs_[type] == NULL) {
			//No FBO found, make one
			GLuint newFBO = NULL;
			glGenFramebuffers(1, &newFBO);

			if (newFBO == NULL) {
				throw std::runtime_error("Unable to generate a new FBO! Press F...");
			}

			FBOs_[type] = newFBO;
		}

		return FBOs_[type];
	}
}