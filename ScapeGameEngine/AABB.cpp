#include "AABB.h"
#include "Mesh.h"

namespace sge {
	inline void inPlaceMin(float& target, float tested) {
		if (tested < target) {
			target = tested;
		}
	}

	inline void inPlaceMax(float& target, float tested) {
		if (tested > target) {
			target = tested;
		}
	}

	AABB::AABB(std::vector<Vertex3D>& vertices) {
		if (vertices.size() < 3) {
			throw std::runtime_error("The vector vertices does not form one or more complete triangles");
		}

		float minX = vertices[0].x, minY = vertices[0].y, minZ = vertices[0].z;
		float maxX = minX, maxY = minY, maxZ = minZ;

		//Find the smallest and biggest values of all vertices
		for (auto& vertex : vertices) {
			inPlaceMin(minX, vertex.x);
			inPlaceMin(minY, vertex.y);
			inPlaceMin(minZ, vertex.z);

			inPlaceMax(maxX, vertex.x);
			inPlaceMax(maxY, vertex.y);
			inPlaceMax(maxZ, vertex.z);
		}

		glm::vec3 minPoint = { minX, minY, minZ };
		glm::vec3 maxPoint = { maxX, maxY, maxZ };

		//Calculate the distance between those points
		dimensions_ = glm::abs(maxPoint - minPoint);

		//Calculate the center of mass (average of those points)
		COM_ = (minPoint + maxPoint) / 2.f;
	}
	AABB AABB::scaled(float x, float y, float z) {
		return AABB(dimensions_ * glm::vec3(x, y, z), COM_ * glm::vec3(x, y, z));

		//TODO: support for non-uniform scaling
	}
}