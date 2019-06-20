#pragma once
#include "stdheaders.h"

namespace sge {
	//Matches VAOType
	namespace ObjectType {
		enum  Enum {
			STATIC,
			DYNAMIC,
			GENERIC
		};
	}

	//A base for all other objects.
	//Don't use this for rendering;
	//You are probably looking for
	//StaticObject if you just want 
	//to render it (to the screen)
	class Object {
	public:
		Object();
		~Object();

		void setPos(float x, float y, float z) { posX_ = x; posY_ = y; posZ_ = z; transformNeedsUpdating = true; }
		void setRot(float x, float y, float z) { rotX_ = x; rotY_ = y; rotZ_ = z; transformNeedsUpdating = true; }

		//I'm going to regret this...
		virtual void render() = 0;

		ObjectType::Enum type() { return type_; }

		//If false, the object should not be rendered
		bool renderObject = true;
	protected:
		float posX_ = 0, posY_ = 0, posZ_ = 0;
		float scaleX_ = 1, scaleY_ = 1, scaleZ_ = 1;
		float rotX_ = 0, rotY_ = 0, rotZ_ = 0;

		glm::mat4x4 cachedMatrix_;

		bool transformNeedsUpdating = true;

		const ObjectType::Enum type_ = ObjectType::GENERIC;
	};
}