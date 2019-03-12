#pragma once
#include "stdheaders.h"
#include "BufferManager.h"

namespace sge {
	struct Vertex3D {
		float x = 0, y = 0, z = 0;
	};

	using VertexArray = std::vector<Vertex3D>;
	using IndexArray = std::vector<GLuint>;

	class Mesh {
	public:
		VertexArray* VertArrayPtr() { return &VertArray_; }
		IndexArray* IndArray() { return &IndArray_; }

		//Do not call this without setting up buffers
		//i.e. use Renderer
		void render();

		Mesh();
		~Mesh();
	private:
		VertexArray VertArray_;
		IndexArray IndArray_;
	};
}