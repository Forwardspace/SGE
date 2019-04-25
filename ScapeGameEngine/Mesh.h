#pragma once
#include "stdheaders.h"
#include "BufferManager.h"

namespace sge {
	struct Vertex3D {
		GLfloat x = 0, y = 0, z = 0;
	};

	struct Vertex2D {
		GLfloat x = 0, y = 0;
	};

	using VertexArray = std::vector<Vertex3D>;
	using IndexArray = std::vector<GLuint>;
	using TexCoordArray = std::vector<Vertex2D>;

	class Mesh {
	public:
		VertexArray* VertArrayPtr() { return &VertArray_; }
		IndexArray* IndArrayPtr() { return &IndArray_; }
		TexCoordArray* TexCoordArrayPtr() { return &TCArray_; }

		void setVertArrayPtr(VertexArray va) { VertArray_ = va; }
		void setIndArrayPtr(IndexArray ia) { IndArray_ = ia; }
		void setTexCoordArray(TexCoordArray ta) { TCArray_ = ta; }

		Mesh();
		Mesh(VertexArray va, IndexArray ia, TexCoordArray ta);
		~Mesh();
	private:
		VertexArray VertArray_;
		IndexArray IndArray_;
		TexCoordArray TCArray_;
	};
}