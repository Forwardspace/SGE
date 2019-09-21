#pragma once
#include "stdheaders.h"
#include "Renderer.h"
#include "UserInputManager.h"
#include "RigidPhysics.h"

namespace sge {
	class FPSCameraController {
	public:
		static void enable();
		static void disable();

		static void update();

		//Configurable variables

		static float mouseSensitivity;	//Default: 10. (unitless)
		static float speed;			//Default: 2. m/s

		static float gravity;	//Default: 9.81 m/s**2

	private:
		static void init();
		static bool inited;

		static bool enabled;

		static float prevX;
		static float prevY;

		static btRigidBody* body;
		static btCollisionShape* collision;
	};
}