#include "Object.h"
#include "Renderer.h"

namespace sge {
	Object::Object() {
	}

	Object::~Object() {
	}

	glm::mat4x4 Object::getMVP() {
		if (transformNeedsUpdating) {
			transformNeedsUpdating = false;
			transformJustUpdated = true;

			updateModelMatrix();
		}
		else {
			transformJustUpdated = false;
		}

		glm::mat4x4 view = Renderer::currentCamera()->viewMatrix();
		glm::mat4x4 projection = Renderer::projectionMatrix();

		return projection * view * cachedMatrix_;
	}

	void Object::clampAngles() {
		rotX_ = (float)fmod(rotX_, 360);
		rotY_ = (float)fmod(rotY_, 360);
		rotZ_ = (float)fmod(rotZ_, 360);
	}

	void Object::updateModelMatrix() {
		clampAngles();

		//Generate the rotation matrix by succesive rotations on every axis.
		glm::mat4x4 rotMat = glm::mat4x4(1);
		rotMat = glm::rotate(rotMat, rotX_, glm::vec3(1, 0, 0));
		rotMat = glm::rotate(rotMat, rotY_, glm::vec3(0, 1, 0));
		rotMat = glm::rotate(rotMat, rotZ_, glm::vec3(0, 0, 1));

		glm::mat4x4 transMat = glm::translate(glm::mat4x4(1), glm::vec3(posX_, posY_, posZ_));
		glm::mat4x4 scaleMat = glm::scale(glm::mat4x4(1), glm::vec3(scaleX_, scaleY_, scaleZ_));

		cachedMatrix_ = transMat * rotMat * scaleMat;
	}
}