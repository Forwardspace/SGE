#include "Camera.h"

namespace sge {
	Camera::Camera() {
	}

	Camera::Camera(float posX, float posY, float posZ) {
		setPos(posX, posY, posZ);
	}

	Camera::Camera(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
		setTransform(pos, rot, scale);
	}

	void Camera::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
		posX_ = pos.x; posY_ = pos.y; posZ_ = pos.z;
		rotX_ = rot.x; posY_ = rot.y; posZ_ = rot.z;
		scaleX_ = scale.x; posY_ = scale.y; posZ_ = scale.z;

		transformNeedsUpdating = true;
	}

	void Camera::setPos(float posX, float posY, float posZ) {
		posX_ = posX;
		posY_ = posY;
		posZ_ = posZ;

		transformNeedsUpdating = true;
	}

	void Camera::setRot(float rotX, float rotY, float rotZ) {
		rotX_ = rotX;
		rotY_ = rotY;
		rotZ_ = rotZ;

		transformNeedsUpdating = true;
	}

	void Camera::clampAngles() {
		rotX_ = fmod(rotX_, 360);
		rotY_ = fmod(rotY_, 360);
		rotZ_ = fmod(rotZ_, 360);
	}

	void Camera::updateViewMatrix() {
		clampAngles();

		float radRotX = glm::radians(rotX_);
		float radRotY = glm::radians(rotY_);
		float radRotZ = glm::radians(rotZ_);

		//cachedMatrix_ = glm::lookAt(glm::vec3(0, 0, -2), glm::vec3(-1, 0, 1), glm::vec3(0, 1, 0));

		//Generate the rotation matrix using the glm::lookAt function

		//Converts spherical to normal, cartesian coordinates
		glm::vec3 direction(
			cos(radRotX) * sin(radRotY),
			sin(radRotX),
			cos(radRotX) * cos(radRotY)
		);

		//Compute the right vector
		glm::vec3 right = glm::vec3(
			sin(radRotY - 3.14f / 2.0f),
			0,
			cos(radRotY - 3.14f / 2.0f)
		);

		//Finally, the up vector
		glm::vec3 up = glm::cross(right, direction);

		//We have all we need, calculate the final matrix
		cachedMatrix_ = glm::lookAt(
			glm::vec3(posX_, posY_, posZ_),
			glm::vec3(posX_, posY_, posZ_) + direction,
			up
		);
	}

	glm::mat4x4 Camera::makeViewMatrix() {
		if (transformNeedsUpdating) {
			transformNeedsUpdating = false;
			updateViewMatrix();
		}

		return cachedMatrix_;
	}

	Camera::~Camera() {
	}
}