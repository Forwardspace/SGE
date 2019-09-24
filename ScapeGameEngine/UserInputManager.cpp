#include "UserInputManager.h"

#include "GLFWIOManager.h"
#include "ScapeGUIMouseState.h"

namespace sge {
	UserInputMapping& UserInputManager::currentMapping_ = FPSControls;

	float UserInputManager::getAxis(std::string axisName) {
		return currentMapping_.axes[axisName];
	}

	bool UserInputManager::pressed(int key) {
		return GLFWIOManager::isPressed(key);
	}

	bool UserInputManager::modPressed(int mod) {
		return GLFWIOManager::mods() & mod;
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
	//First, there are the required axes with default values
	//Second, there are weights for each key for each axis
	//This is the default mapping, and is the one FPSController uses
	UserInputMapping FPSControls = {
		{ {"X", 0}, {"Y", 0} },
		{
			{GLFW_KEY_W, { {"Y", 1.f} }},
			{GLFW_KEY_S, { {"Y", -1.f} }},
			{GLFW_KEY_A, { {"X", -1.f} }},
			{GLFW_KEY_D, { {"X", 1.f} }},
		}
	};
}