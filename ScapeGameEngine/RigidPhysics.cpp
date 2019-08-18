#include "RigidPhysics.h"
#include "Object.h"

namespace sge {
	RigidPhysicsObject::RigidPhysicsObject(
		BasicColliderType type,
		glm::vec3 scale,
		glm::dvec3 objectPos,
		glm::dvec3 objectRot,
		float objectMass
	) {
		colliderType = (int)type;
		dims_ = scale;

		switch (type) {
		case BasicColliderType::BOX:
			createBox();
			break;
		case BasicColliderType::SPHERE:
			createSphere();
			break;
		}

		//Create the rigid body itself
		//Convert from glm::mat4 to btTransform
		btTransform t;
		t.setOrigin((const btVector3&)objectPos);
		t.setRotation((const btQuaternion&)glm::dquat(objectRot));
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

	void RigidPhysicsObject::update(Object* parent) {
		auto motionState = body_->getMotionState();
		
		btTransform transform;
		motionState->getWorldTransform(transform);

		//Update the parent object
		//First decompose the transform into translate and rotate vec3s,
		glm::dvec3 translate = (glm::dvec3&)transform.getOrigin();
		glm::dquat basis = (glm::dquat&)transform.getRotation();
		glm::dvec3 rotation = glm::eulerAngles(basis);

		if ((glm::vec3)translate != parent->pos()) {
			parent->setPos(translate);
		}
		if ((glm::vec3)rotation != parent->rot()) {
			parent->setRot(rotation);
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

	BoxCollider::BoxCollider(double x, double y, double z) {
		shape = new btBoxShape(btVector3(x, y, z));
	}
	
	SphereCollider::SphereCollider(double r) {
		shape = new btSphereShape(r);
	}
}