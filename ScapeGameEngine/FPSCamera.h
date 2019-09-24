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
		static float sprintSpeed;	//Default: 2 (times normal speed)
		static float walkSpeed;		//Default: 0.5 (times normal speed)

		static float gravity;		//Default: 9.81 m/s**2
		static float jumpStrength;	//Default 5 m/s**2

	private:
		static void init();
		static bool inited;

		static bool enabled;

		static float prevX;
		static float prevY;

		static float jumpVelocity;

		static btRigidBody* body;
		static btCollisionShape* collision;
	};
}