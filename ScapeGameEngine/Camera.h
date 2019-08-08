#pragma once
#include "stdheaders.h"

namespace sge {
	//The most important purpose of Camera is
	//storing its view matrix (and therefore, its 
	//position and orientation)
	class Camera {
	public:
		Camera();
		//Camera from position
		Camera(float posX, float posY, float posZ);
		//Camera from transform
		Camera(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

		glm::mat4x4 viewMatrix() { return makeViewMatrix(); }

		void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
		void setPos(float posX, float posY, float posZ);
		void setRot(float rotX, float rotY, float rotZ);

		glm::vec3 pos() { return glm::vec3(posX_, posY_, posZ_); }
		glm::vec3 rot() { return glm::vec3(rotX_, rotY_, rotZ_); }

		~Camera();
	private:
		glm::mat4x4 makeViewMatrix();
		void updateViewMatrix();

		void clampAngles();

		float posX_ = 0, posY_ = 0, posZ_ = 0;
		float rotX_ = 0, rotY_ = 0, rotZ_ = 0;
		float scaleX_ = 1, scaleY_ = 1, scaleZ_ = 1;

		glm::mat4x4 cachedMatrix_;

		//We don't waste cycles here!
		bool transformNeedsUpdating = true;
	};
}