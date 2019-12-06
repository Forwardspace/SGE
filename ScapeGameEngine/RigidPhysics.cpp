#include "RigidPhysics.h"
#include "Object.h"
#include "AABB.h"

namespace sge {
	RigidPhysicsObject::RigidPhysicsObject(
		BasicColliderType type,
		AABB boundingBox,
		glm::vec3 objectPos,
		glm::vec3 objectRot,
		float objectMass,
		Object* parent
	) {
		colliderType = (int)type;
		parent_ = parent;

		//Bullet seems to have an issue with scaling, correct that here
		dims_ = boundingBox.getDimensions() / 2.f;

		//While we're here, get the center of mass
		center_ = boundingBox.getCOM();

		switch (type) {
		case BasicColliderType::BOX:
			createBox();
			break;
		case BasicColliderType::SPHERE:
			createSphere();
			break;
		}

		//Create the rigid body itself
		//Offset the collider to be in the middle of the object
		auto finalPos = (btVector3&)(objectPos + center_);

		btTransform t;
		t.setOrigin(finalPos);
		t.setRotation((const btQuaternion&)glm::quat(objectRot));

		auto motionState = new btDefaultMotionState(t);

		btVector3 inertia = btVector3(0, 0, 0);
		if (objectMass > 0) {
			//The object isn't static, calculate its inertia
			collider_->calculateInertia(objectMass, inertia);
		}

		btRigidBody::btRigidBodyConstructionInfo info(objectMass, motionState, collider_->shape, inertia);
		body_ = new btRigidBody(info);

		if (objectMass == 0) {
			//Disable deactivation due to the object not moving
			body_->setActivationState(DISABLE_DEACTIVATION);
		}
		else {
			//Make this object dynamic
			body_->setCollisionFlags(
				body_->getCollisionFlags() & ~(btCollisionObject::CF_STATIC_OBJECT | btCollisionObject::CF_KINEMATIC_OBJECT)
			);
		}

		//Add the new body to the global world
		BulletIOManager::world()->addRigidBody(body_);
	}

	RigidPhysicsObject::~RigidPhysicsObject() {
		delete collider_;
	}

	extern double deltaTime;

	void RigidPhysicsObject::update() {
		auto motionState = body_->getMotionState();
		
		btTransform transform;
		motionState->getWorldTransform(transform);

		//Update the parent object
		//First decompose the transform into translate and rotate vec3s,
		glm::vec3 translate = (glm::vec3&)transform.getOrigin();
		glm::quat rotQuat = (glm::quat&)transform.getRotation();
		glm::vec3 rotation = glm::eulerAngles(rotQuat);

		//De-translate (un-translate?) the center of mass to get
		//the actual position
		translate -= center_ * 1.25f;

		//Apply the gravity
		if (physGravity > 0) {
			auto grav = physGravityNormal * physGravity / body_->getInvMass();

			if (1.f / body_->getInvMass() != 0) {
				body_->applyCentralForce((btVector3&)grav);
			}
		}

		if ((glm::vec3)translate != parent_->pos()) {
			parent_->setPos(translate);
		}
		if ((glm::vec3)rotation != parent_->rot()) {
			parent_->setRot(rotation);
		}
		//Don't update scale; not much of a rigid body if it isn't rigid
	}

	void RigidPhysicsObject::createBox() {
		collider_ = new BoxCollider(dims_.x, dims_.y, dims_.z);
	}

	void RigidPhysicsObject::createSphere() {
		collider_ = new SphereCollider(dims_.r);
	}

	//COLLIDERS//
	
	void Collider::calculateInertia(float mass, btVector3& inertia) {
		shape->calculateLocalInertia(mass, inertia);
	}

	Collider::~Collider() {
		delete shape;
	}

	BoxCollider::BoxCollider(float x, float y, float z) {
		shape = new btBoxShape(btVector3(x, y, z));
	}
	
	SphereCollider::SphereCollider(float r) {
		shape = new btSphereShape(r);
	}
	
	void InstancedRigidPhysicsObject::update() {
		for (auto instance : instances_) {
			instance->update();
		}
	}
	
	void InstancedRigidPhysicsObject::addInstance(RigidPhysicsObject* instance) {
		instances_.push_back(instance);
	}
	
	void InstancedRigidPhysicsObject::removeInstance(RigidPhysicsObject* instance) {
		auto pos = std::find(instances_.begin(), instances_.end(), instance);
		instances_.erase(pos);
	}
}