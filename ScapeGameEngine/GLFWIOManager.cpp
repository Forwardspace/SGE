#include "GLFWIOManager.h"

namespace sge {
	bool GLFWIOManager::storeText_ = false;
	std::wstring GLFWIOManager::textBuffer_;
	double GLFWIOManager::mouseX_ = 0, GLFWIOManager::mouseY_ = 0;
	std::array<bool, 8> GLFWIOManager::mouseKeyStatus_ {};

	void GLFWIOManager::init(GLFWwindow* wind_) {
		glfwSetCharCallback(wind_, charCallback);
		glfwSetCursorPosCallback(wind_, cursorPosCallback);
		glfwSetKeyCallback(wind_, keyCallback);
		glfwSetMouseButtonCallback(wind_, mouseButtonCallback);
	}

	void GLFWIOManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	}

	void GLFWIOManager::charCallback(GLFWwindow* window, GLuint codepoint) {
		if (storeText_) {
			textBuffer_ += codepoint;
		}
	}

	void GLFWIOManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
		mouseX_ = xpos;
		mouseY_ = ypos;
	}

	void GLFWIOManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			//Update key state to 1
			mouseKeyStatus_[button] = true;
		}
		else {
			//Update it to 0
			mouseKeyStatus_[button] = false;
		}
	}
}