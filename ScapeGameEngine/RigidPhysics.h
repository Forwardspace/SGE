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

	class Object;
	//Represents an object that simulates real-world physics
	//Used by Objects
	class RigidPhysicsObject : public PhysicsObject {
	public:
		RigidPhysicsObject(
			BasicColliderType type,
			AABB boundingBox,
			glm::vec3 objectPos,
			glm::vec3 objectRot,
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

		glm::vec3 dims_;
		glm::vec3 center_;

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
		BoxCollider(float x, float y, float z);
	};

	//The collider here is a simple sphere of radius r
	class SphereCollider : public Collider {
	public:
		SphereCollider(float r);
	};
}