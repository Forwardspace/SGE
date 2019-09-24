#include "BulletIOManager.h"
#include "Object.h"
#include "RigidPhysics.h"

namespace sge {
	glm::dvec3 physGravityNormal = { 0, -1, 0 };
	double physGravity = 9.81;

	bool BulletIOManager::simulate = true;
	btDiscreteDynamicsWorld* BulletIOManager::world_;

	extern double deltaTime;
	
	void BulletIOManager::init() {
		//Bullet sure does love OOP

		auto collisionConfiguration = new btDefaultCollisionConfiguration();
		auto dispatcher = new btCollisionDispatcher(collisionConfiguration);
		//ToDo: use multithreaded dispatcher?

		//Honestly, no clue what this does
		auto overlappingPairCache = new btDbvtBroadphase();

		auto solver = new btSequentialImpulseConstraintSolver;

		world_ = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

		//Disable predefined gravity, apply it manually
		world_->setGravity(btVector3(0, 0, 0));
	}

	void BulletIOManager::update(std::deque<Object*> objects) {
		if (!simulate) {
			//The simulation is suspended - skip all updating
			return;
		}

		world_->stepSimulation(deltaTime, 1);

		//Loop through all objects and update them
		for (auto object : objects) {
			//Figure out the physics object's type and update it
			if (object->physObj_) {
				object->physObj_->update();
			}
		}
	}

	void BulletIOManager::terminate() {
		delete world_;
	}
	
	std::array<glm::vec3, 2> decomposeBtTransform(btTransform target) {
		auto translation = target.getOrigin();
		glm::vec3 glmTranslation = glm::vec3(translation.getX(), translation.getY(), translation.getZ());
		glm::dvec3 eulerRot = glm::eulerAngles((glm::dquat&)target.getRotation());

		return { glmTranslation, eulerRot };
	}
}