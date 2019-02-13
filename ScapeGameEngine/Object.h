#pragma once

namespace sge {
	//A base for all other objects
	//Don't use this for rendering
	//You are probably looking for
	//StaticObject if you jut want
	//to render it (to the screen)
	class Object {
	public:
		Object();
		~Object();

	protected:
		double posX = 0, posY = 0, posZ = 0;
		double scaleX = 1, scaleY = 1, scaleZ = 1;
		double rotX = 0, rotY = 0, rotZ = 0;
	};
}