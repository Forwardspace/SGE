#include "FPSCamera.h"

namespace sge {
	float FPSCamera::mouseSensitivity = 5.0f;
	float FPSCamera::speed = 0.1f;

	float FPSCamera::prevX = 0;
	float FPSCamera::prevY = 0;

	void FPSCamera::enable() {
		Renderer::registerWindowCallback(update);
		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void FPSCamera::disable() {
		Renderer::removeWindowCallback(update);
		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void FPSCamera::update() {
		Camera* maincam = Renderer::currentCamera();

		float mY = sge::GLFWIOManager::mouseX();
		float deltaY = mY - prevY;
		deltaY *= (1 / mouseSensitivity);

		float mX = sge::GLFWIOManager::mouseY();
		float deltaX = mX - prevX;
		deltaX *= (1 / mouseSensitivity);

		float velZ = speed * UserInputManager::getAxis("Y");
		float velX = speed * UserInputManager::getAxis("X");

		glm::vec3 camRot(190 - deltaX, -deltaY, 0);
		if (maincam->rot() != camRot) {
			maincam->setRot(camRot.x, camRot.y, camRot.z);
		}

		//Calculate where to move to based on the camera's
		//orientation
		glm::vec3 pos = maincam->pos();
		glm::mat4 view = maincam->viewMatrix();

		glm::vec3 forward = glm::vec3(view[0][2], view[1][2], view[2][2]);
		glm::vec3 right = glm::vec3(view[0][0], view[1][0], view[2][0]);

		glm::vec3 deltaPosZ = forward * velZ;
		glm::vec3 deltaPosX = right * velX;

		glm::vec3 deltaPos = deltaPosX - deltaPosZ;
		pos += deltaPos;

		if (maincam->pos() != pos) {
			maincam->setPos(pos.x, pos.y, pos.z);
		}
	}
}