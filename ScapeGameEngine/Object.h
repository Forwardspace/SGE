#pragma once
#include "stdheaders.h"

namespace sge {
	enum class ObjectType {
		STATIC,
		INSTANCED_STATIC,
		GENERIC,
		INSTANCE
	};

	//A base for all other objects.
	class Object {
	public:
		Object();
		~Object();

		void setPos(float x, float y, float z) { posX_ = x; posY_ = y; posZ_ = z; transformNeedsUpdating = true; }
		void setRot(float x, float y, float z) { rotX_ = x; rotY_ = y; rotZ_ = z; transformNeedsUpdating = true; }

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

		ObjectType type_ = ObjectType::GENERIC;
	};
}