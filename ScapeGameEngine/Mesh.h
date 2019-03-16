#pragma once
#include "stdheaders.h"
#include "BufferManager.h"

namespace sge {
	struct Vertex3D {
		GLfloat x = 0, y = 0, z = 0;
	};

	using VertexArray = std::vector<Vertex3D>;
	using IndexArray = std::vector<GLuint>;

	class Mesh {
	public:
		VertexArray* VertArrayPtr() { return &VertArray_; }
		IndexArray* IndArrayPtr() { return &IndArray_; }

		void setVertArrayPtr(VertexArray va) { VertArray_ = va; }
		void setIndArrayPtr(IndexArray ia) { IndArray_ = ia; }

		Mesh();
		Mesh(VertexArray va, IndexArray ia);
		~Mesh();
	private:
		VertexArray VertArray_;
		IndexArray IndArray_;
	};
}