#pragma once
#include "stdheaders.h"

namespace sge {
	struct Vertex3D;

	//Axis-aligned bounding box
	//perfectly encases the given vertices
	class AABB {
	public:
		AABB() {}
		AABB(glm::vec3 scale) { dimensions_ = scale; COM_ = glm::vec3(0, 0, 0); }
		AABB(glm::vec3 scale, glm::vec3 COM) { dimensions_ = scale; COM_ = COM; }

		AABB(std::vector<Vertex3D>& vertices);

		//Get the minimum and maximum points of the box, in that order
		glm::vec3 getDimensions() { return dimensions_; }
		//Get the Center of Mass of the object
		glm::vec3 getCOM() { return COM_; }

		AABB scaled(float x, float y, float z);

	private:
		glm::vec3 dimensions_;
		glm::vec3 COM_;
	};
}
