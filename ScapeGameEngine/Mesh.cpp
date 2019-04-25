#include "Mesh.h"

namespace sge {
	Mesh::Mesh() {
	}

	Mesh::Mesh(VertexArray va, IndexArray ia, TexCoordArray ta) {
		VertArray_ = va;
		IndArray_ = ia;
		TCArray_ = ta;
	}

	Mesh::~Mesh() {
	}
}