#pragma once

namespace sge {
	//This is empty so that it can be dynamic_casted into derived classes
	//as needed
	class PhysicsObject {
	public:
		virtual ~PhysicsObject() {};
		virtual void update() = 0;
	};
}