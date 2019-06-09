#pragma once
#include "stdheaders.h"
#include "Renderer.h"
#include "UserInputManager.h"

namespace sge {
	class FPSCamera {
	public:
		FPSCamera() = delete;	//Singleton
		~FPSCamera() = delete;

		static void enable();
		static void disable();

		static void update();

		//Configurable variables

		static float mouseSensitivity;	//Default: 5
		static float speed;			//Default: 0.1

	private:
		static float prevX;
		static float prevY;
	};
}