#pragma once
#include "stdheaders.h"
#include "BufferManager.h"
#include "IOManager.h"

namespace sge {
	struct  Vertex3D {
		Vertex3D(GLfloat X, GLfloat Y) { x = X; y = Y; }
		Vertex3D(GLfloat X, GLfloat Y, GLfloat Z) { x = X; y = Y; z = Z; }
		Vertex3D(aiVector3D aiv3d) { x = aiv3d.x; y = aiv3d.y; z = aiv3d.z; }
		GLfloat x = 0, y = 0, z = 0;
	};

	struct  Vertex2D {
		Vertex2D(GLfloat X, GLfloat Y) { x = X; y = Y; }
		Vertex2D(Vertex3D v3d) { x = v3d.x; y = v3d.y; /* Ignore Z */ }
		Vertex2D(aiVector3D aiv3d) { x = aiv3d.x; y = aiv3d.y; /* Ignore Z */ }
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

		void appendMeshData(const aiScene* scene, aiMesh* mesh);

		Mesh();
		Mesh(VertexArray va, IndexArray ia, TexCoordArray ta);
		//Mesh from file: loads the first mesh from the file
		//given. Called automatically.
		Mesh(fs::path filename);
		~Mesh();
	private:
		VertexArray VertArray_;
		IndexArray IndArray_;
		TexCoordArray TCArray_;
	};
}