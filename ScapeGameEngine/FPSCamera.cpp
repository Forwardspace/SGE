#include "FPSCamera.h"

namespace sge {
	double FPSCamera::mouseSensitivity = 5;
	double FPSCamera::speed = 0.1;

	double FPSCamera::prevX = 0;
	double FPSCamera::prevY = 0;

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

		double mouseSensitivity = 5;
		double speed = 0.1;

		double mY = sge::GLFWIOManager::mouseX();
		double deltaY = mY - prevY;
		deltaY *= (1 / mouseSensitivity);

		double mX = sge::GLFWIOManager::mouseY();
		double deltaX = mX - prevX;
		deltaX *= (1 / mouseSensitivity);

		float velZ = speed * UserInputManager::getAxis("Y");
		float velX = speed * UserInputManager::getAxis("X");

		maincam->setRot(180 - deltaX, -deltaY, 0);

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

		maincam->setPos(pos.x, pos.y, pos.z);
	}
}