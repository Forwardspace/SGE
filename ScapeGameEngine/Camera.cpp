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
		rotX_ = rot.x; rotY_ = rot.y; rotZ_ = rot.z;
		scaleX_ = scale.x; scaleY_ = scale.y; scaleZ_ = scale.z;

		transformNeedsUpdating_ = true;
	}

	void Camera::setPos(float posX, float posY, float posZ) {
		posX_ = posX;
		posY_ = posY;
		posZ_ = posZ;

		transformNeedsUpdating_ = true;
	}

	void Camera::setRot(float rotX, float rotY, float rotZ) {
		rotX_ = rotX;
		rotY_ = rotY;
		rotZ_ = rotZ;

		transformNeedsUpdating_ = true;
	}

	void Camera::clampAngles() {
		rotX_ = (float)fmod(rotX_, 360);
		rotY_ = (float)fmod(rotY_, 360);
		rotZ_ = (float)fmod(rotZ_, 360);
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
			sin(radRotY - glm::pi<float>() / 2.0f),
			0,
			cos(radRotY - glm::pi<float>() / 2.0f)
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
		if (transformNeedsUpdating_) {
			transformNeedsUpdating_ = false;
			updateViewMatrix();

			transformJustUpdated_ = true;
		}
		else {
			transformJustUpdated_ = false;
		}

		return cachedMatrix_;
	}

	Camera::~Camera() {
	}
}