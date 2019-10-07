#pragma once
#include "stdheaders.h"
#include "PhysicsObject.h"

namespace sge {
	class BulletIOManager;

	enum class ObjectType {
		STATIC,
		INSTANCED_STATIC,
		GENERIC,
		INSTANCE,
		MONO_SCRIPTED
	};

	inline void unpackVec3(float& x, float& y, float& z, glm::vec3 target) {
		x = target.x; y = target.y; z = target.z;
	}

	//A base for all other objects.
	class Object {
	public:
		Object();
		virtual ~Object();

		inline void setPos(float x, float y, float z) { posX_ = x; posY_ = y; posZ_ = z; transformNeedsUpdating = true; }
		inline void setRot(float x, float y, float z) { rotX_ = x; rotY_ = y; rotZ_ = z; transformNeedsUpdating = true; }
		inline void setScl(float x, float y, float z) { scaleX_ = x; scaleY_ = y; scaleZ_ = z; transformNeedsUpdating = true; }

		inline void setPos(glm::vec3 v) { unpackVec3(posX_, posY_, posZ_, v); transformNeedsUpdating = true; }
		inline void setRot(glm::vec3 v) { unpackVec3(rotX_, rotY_, rotZ_, v); transformNeedsUpdating = true; }
		inline void setScl(glm::vec3 v) { unpackVec3(scaleX_, scaleY_, scaleZ_, v); transformNeedsUpdating = true; }

		inline glm::vec3 pos() { return { posX_, posY_, posZ_ }; }
		inline glm::vec3 rot() { return { rotX_, rotY_, rotZ_ }; }
		inline glm::vec3 scl() { return { scaleX_, scaleY_, scaleZ_ }; }

		inline glm::mat4 modelMat() {
			if (transformNeedsUpdating) {
				updateModelMatrix();

				transformNeedsReplacing = true;
			}
			return cachedMatrix_;
		}

		virtual void render() = 0;
		virtual void setupVAO() = 0;

		ObjectType type() { return type_; }

		//If false, the object should not be rendered
		bool renderObject = true;
	protected:
		glm::mat4x4 getMVP();
		void updateModelMatrix();
		void clampAngles();

		float posX_ = 0, posY_ = 0, posZ_ = 0;
		float scaleX_ = 1, scaleY_ = 1, scaleZ_ = 1;
		float rotX_ = 0, rotY_ = 0, rotZ_ = 0;

		glm::mat4x4 cachedMatrix_;

		bool transformNeedsUpdating = true;
		bool transformJustUpdated = false;
		bool transformNeedsReplacing = true;	//This flag is used when moving transforms inside VBOs

		ObjectType type_ = ObjectType::GENERIC;

		//Used for physics
		PhysicsObject* physObj_ = nullptr;
		friend class BulletIOManager;
		friend class RigidPhysicsObject;
	};
}