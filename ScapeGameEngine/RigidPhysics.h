#pragma once
#include "stdheaders.h"
#include "BulletIOManager.h"
#include "PhysicsObject.h"

namespace sge {
	enum class BasicColliderType {
		BOX,
		SPHERE,
	};

	class Collider {
	public:
		btCollisionShape* shape;

		void calculateInertia(float mass, btVector3& inertia);

		virtual ~Collider();
	};

	/*void destroyRigidBodyCallback(const NewtonWorld* const world, void* const listenerUserData, NewtonBody* const body);
	void rigidBodyForceAndTorqueCallback(const NewtonBody* const body, float timestep, int threadIndex);
	void rigidBodyTransformCallback(const NewtonBody* const body, const float* const matrix, int threadIndex);
	*/

	//Represents an object that simulates real-world physics
	//Used by Objects
	class RigidPhysicsObject : public PhysicsObject {
	public:
		RigidPhysicsObject(
			BasicColliderType type,
			glm::vec3 scale,
			glm::dvec3 objectPos,
			glm::dvec3 objectRot,
			float objectMass
		);
		~RigidPhysicsObject();

		int colliderType;
		Collider* collider() { return collider_; }
		
		void update(Object* parent);

		bool gravity = true;

	private:
		Collider* collider_;
		btRigidBody* body_;

		void createBox();
		void createSphere();

		glm::vec3 dims_;
	};

	//The most often used collider
	//In this case, the collider is a simple 3d box
	class BoxCollider : public Collider {
	public:
		BoxCollider(double x, double y, double z);
	};

	//The collider here is a simple sphere of radius r
	class SphereCollider : public Collider {
	public:
		SphereCollider(double r);
	};
}