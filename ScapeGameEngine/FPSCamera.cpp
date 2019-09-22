#include "FPSCamera.h"

namespace sge {
	float FPSCameraController::mouseSensitivity = 0.2f;

	float FPSCameraController::speed = 5.f;
	float FPSCameraController::sprintSpeed = 2.f;
	float FPSCameraController::walkSpeed = 0.5f;

	float FPSCameraController::gravity = 9.81f;
	float FPSCameraController::jumpStrength = 4.f;

	float FPSCameraController::prevX = 0;
	float FPSCameraController::prevY = 0;

	bool FPSCameraController::inited = false;
	bool FPSCameraController::enabled = false;

	float FPSCameraController::jumpVelocity = 0;

	btRigidBody* FPSCameraController::body;
	btCollisionShape* FPSCameraController::collision;

	const double playerMass = 70;	//kg
	const double playerHeight = 1.8 * 2; //m, account for the weird bullet scaling

	//Casts a ray from pos downwards to rayLength, returns true if the ray hit anything
	bool raycastDown(glm::vec3 pos, float rayLength) {
		rayLength += 0.01;	//Add some room for error

		//Cast from the controller to just past the "legs" of the character
		glm::dvec3 rayStart = pos;
		glm::dvec3 rayEnd = (glm::dvec3)pos + glm::dvec3(0, -rayLength, 0);

		btCollisionWorld::ClosestRayResultCallback rayHit((btVector3&)rayStart, (btVector3&)rayEnd);
		BulletIOManager::world()->rayTest((btVector3&)rayStart, (btVector3&)rayEnd, rayHit);

		return rayHit.hasHit();
	}

	void FPSCameraController::init() {
		Renderer::registerWindowCallback(update);

		Camera* maincam = Renderer::currentCamera();
		if (!maincam) {
			throw std::runtime_error("Camera is nullptr in FPSCamera.");
		}

		//Create a capsule rigid body collider for the player

		btVector3 calculatedInertia;

		collision = new btCapsuleShape(0.5 * 2, playerHeight);
		collision->calculateLocalInertia(playerMass, calculatedInertia);

		btTransform t;
		t.setOrigin((btVector3&)glm::dvec3(maincam->pos()));
		t.setRotation((btQuaternion&)glm::dquat(maincam->rot()));

		auto motionState = new btDefaultMotionState(t);

		auto info = btRigidBody::btRigidBodyConstructionInfo(playerMass, motionState, collision, calculatedInertia);
		body = new btRigidBody(info);

		body->setActivationState(DISABLE_DEACTIVATION);
		BulletIOManager::world()->addRigidBody(body);
	}

	void FPSCameraController::enable() {
		if (!inited) {
			init();
			inited = true;
		}

		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		enabled = true;
	}

	void FPSCameraController::disable() {
		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		enabled = false;
	}

	inline void sprintOrWalk(float& velZ, float walkSpeed, float sprintSpeed);
	inline glm::vec3 forwardFromMatrix(const glm::mat4& mat);
	inline glm::vec3 rightFromMatrix(const glm::mat4& mat);

	void FPSCameraController::update() {
		if (!enabled) {
			return;
		}

		Camera* maincam = Renderer::currentCamera();

		if (!maincam) {
			return;
		}

		//Extract the position of the rigid body
		btTransform worldTrans;
		body->getMotionState()->getWorldTransform(worldTrans);

		glm::dmat4 camMat(1);

		//Calculate and apply the rotation ONLY TO THE CAMERA
		//there is no reason for the rigid body to rotate
		float mY = sge::GLFWIOManager::mouseX();
		float deltaY = mY - prevY;
		deltaY *= (1 / mouseSensitivity);

		float mX = sge::GLFWIOManager::mouseY();
		float deltaX = mX - prevX;
		deltaX *= (1 / mouseSensitivity);

		auto rot = glm::eulerAngleXYZ(deltaX * 0.001, deltaY * 0.001, 0.);
		camMat *= rot;

		//Apply the position itself to the camera
		glm::dmat4 transMat(1);

		auto orig = worldTrans.getOrigin();
		transMat[3][0] = orig.x();
		transMat[3][1] = orig.y();
		transMat[3][2] = orig.z();

		camMat *= transMat;

		maincam->setTransform(camMat);

		//Now move and rotate the rigidbody
		//First calculate and apply the velocity on the rigidbody to get it to move
		float velZ = speed * UserInputManager::getAxis("Y");
		float velX = speed * UserInputManager::getAxis("X");

		//Simulate sprinting with shift and walking with ctrl
		sprintOrWalk(velZ, walkSpeed, sprintSpeed);

		//Calculate where to move to based on the camera's
		//orientation
		glm::vec3 pos = maincam->pos();
		glm::mat4 view = maincam->viewMatrix();

		//This extracts the vectors directly from the view matrix
		glm::vec3 forward = forwardFromMatrix(view);
		glm::vec3 right = rightFromMatrix(view);

		//Constrain the velocities to their respective axes
		forward.y = 0;
		right.y = 0;

		forward = glm::normalize(forward);
		right = glm::normalize(right);

		glm::vec3 deltaVelZ = forward * velZ;
		glm::vec3 deltaVelX = right * velX;

		glm::vec3 deltaVel = glm::vec3(0, 0, 0);
		deltaVel += deltaVelZ;
		deltaVel += -deltaVelX;

		//Apply gravity or ignore it if jumping
		if (jumpVelocity > 0) {
			deltaVel.y -= jumpVelocity;

			jumpVelocity -= gravity * deltaTime * 5;
		}
		else {
			deltaVel.y += gravity;
		}

		body->setLinearVelocity(btVector3(deltaVel.x, deltaVel.y, deltaVel.z));

		//Constrain the rotation of the rigid body so it doesn't fall over
		auto motion = body->getMotionState();
		btTransform trans;
		motion->getWorldTransform(trans);

		trans.setRotation(btQuaternion::getIdentity());

		motion->setWorldTransform(trans);
		body->setMotionState(motion);
	}

	inline void sprintOrWalk(float& velZ, float walkSpeed, float sprintSpeed) {
		if (UserInputManager::modPressed(GLFW_MOD_CONTROL)) {
			velZ *= walkSpeed;
		}
		else if (UserInputManager::modPressed(GLFW_MOD_SHIFT)) {
			velZ *= sprintSpeed;
		}
	}

	inline glm::vec3 forwardFromMatrix(const glm::mat4& mat) {
		return glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
	}

	inline glm::vec3 rightFromMatrix(const glm::mat4& mat) {
		return glm::vec3(mat[0][0], mat[1][0], mat[2][0]);
	}
}