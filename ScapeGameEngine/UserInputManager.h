#pragma once
#include "stdheaders.h"
#include "GLFWIOManager.h"

namespace sge {
	//Defines a mapping from specific keys to weights
	//axes defines the inital values for any axes
	//weights defines which key influences which axis, and how much
	struct UserInputMapping {
		std::map<std::string, float> axes;
		std::map<int, std::map<std::string, float>> weights;
	};

	class UserInputManager {
	public:
		UserInputManager() = delete;	//Singleton
		~UserInputManager() = delete;

		static void update();

		/////Keyboard/////
		static float getAxis(std::string axisName);
		static bool pressed(int keyCode);
		static bool modPressed(int mod);

		static void setActiveMapping(UserInputMapping& mapping);

		/////Mouse/////
		static int mouseX() { return GLFWIOManager::mouseX(); }
		static int mouseY() { return GLFWIOManager::mouseY(); }
	private:
		static UserInputMapping& currentMapping_;

		static void updateKeyboard();
	};

	extern UserInputMapping FPSControls;

	extern double deltaTime;
}
