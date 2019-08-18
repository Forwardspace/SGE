#pragma once
#include "stdheaders.h"

namespace sge {
	struct Vertex3D;

	//Axis-aligned bounding box
	//perfectly encases the given vertices
	class AABB {
	public:
		AABB() {}
		AABB(std::vector<Vertex3D>& vertices);

		//Get the minimum and maximum points of the box, in that order
		glm::vec3 getDimensions();

	private:
		glm::vec3 dimensions_;
	};
}
