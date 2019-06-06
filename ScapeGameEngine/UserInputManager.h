#pragma once
#include "stdheaders.h"

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

		static float getAxis(std::string axisName);
		static bool pressed(int keyCode);

		static void setActiveMapping(UserInputMapping& mapping);

		static void update();
		static void endFrame();
	private:
		static UserInputMapping& currentMapping_;
	};

	extern UserInputMapping FreeCamControls;

	extern double deltaTime;
}
