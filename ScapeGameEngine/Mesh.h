#pragma once
#include "stdheaders.h"

namespace sge {
	struct Vertex3D {
		float x = 0, y = 0, z = 0;
	};

	using VertexArray = std::vector<Vertex3D>;

	class Mesh {
	public:
		VertexArray* VertArrayPtr() { return &VertArray_; }

		Mesh();
		~Mesh();
	private:
		VertexArray VertArray_;
	};
}