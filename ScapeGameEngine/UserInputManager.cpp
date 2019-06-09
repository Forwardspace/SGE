#include "UserInputManager.h"

#include "GLFWIOManager.h"

namespace sge {
	UserInputMapping& UserInputManager::currentMapping_ = FreeCamControls;

	float UserInputManager::getAxis(std::string axisName) {
		return currentMapping_.axes[axisName];
	}

	bool UserInputManager::pressed(int key) {
		return GLFWIOManager::isPressed(key);
	}

	void UserInputManager::setActiveMapping(UserInputMapping& mapping) {
		currentMapping_ = mapping;
	}

	void UserInputManager::updateKeyboard() {
		//Reset all weights to zero
		for (auto& pair : currentMapping_.axes) {
			std::get<1>(pair) = 0;
		}

		//Update them according to weights
		for (auto& pair : currentMapping_.weights) {
			if (GLFWIOManager::isPressed(std::get<0>(pair))) {
				for (auto& weight : std::get<1>(pair)) {
					currentMapping_.axes[std::get<0>(weight)] += std::get<1>(weight);
				}
			}
		}
	}

	void UserInputManager::update() {
		updateKeyboard();
	}

	//An example of the UIM this class uses:
	//First, there are the required axes
	//Second, there are weights for each key
	UserInputMapping FreeCamControls = {
		{ {"X", 0}, {"Y", 0} },
		{
			{GLFW_KEY_W, { {"Y", 1} }},
			{GLFW_KEY_S, { {"Y", -1} }},
			{GLFW_KEY_A, { {"X", -1} }},
			{GLFW_KEY_D, { {"X", 1} }}
		}
	};
}