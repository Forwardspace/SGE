#pragma once
#include "stdheaders.h"
#include "Object.h"

namespace sge {
	//Manages Newton directly
	class BulletIOManager {
	public:
		static void init();
		static void update(std::deque<Object*> objects); //Called once per frame
		static void terminate();

		BulletIOManager() = delete;	//Singleton
		~BulletIOManager() = delete;

		static btDiscreteDynamicsWorld* world() { return world_; }

		//Default - true
		//Set to false if you don't want to simulate physics,
		//permanently or temporarily
		static bool simulate;

	private:
		static btDiscreteDynamicsWorld* world_;
	};

	//Given a 4 by 4 matrix, this returns an array of,
	//in order, translation, scale and rotation matrices
	std::array<glm::vec3, 2> decomposeBtTransform(btTransform target);
}
