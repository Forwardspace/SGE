#pragma once
#include "stdheaders.h"
#include "BulletIOManager.h"
#include "PhysicsObject.h"
#include "AABB.h"

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

	class Object;
	//Represents an object that simulates real-world physics
	//Used by Objects
	class RigidPhysicsObject : public PhysicsObject {
	public:
		RigidPhysicsObject(
			BasicColliderType type,
			AABB boundingBox,
			glm::dvec3 objectPos,
			glm::dvec3 objectRot,
			float objectMass,
			Object* parent
		);
		~RigidPhysicsObject();

		int colliderType;
		Collider* collider() { return collider_; }
		
		void update();

		bool gravity = true;

	protected:
		Collider* collider_;
		btRigidBody* body_;

		void createBox();
		void createSphere();

		glm::dvec3 dims_;
		glm::dvec3 center_;

		Object* parent_;
	};

	//Used for the master object, updates all child instances
	class InstancedRigidPhysicsObject : public PhysicsObject {
	public:
		void update();

		void addInstance(RigidPhysicsObject* instance);
		void removeInstance(RigidPhysicsObject* instance);

	private:
		std::vector<RigidPhysicsObject*> instances_;
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