#include "Mesh.h"

namespace sge {
	Mesh::Mesh() {
	}

	Mesh::Mesh(VertexArray va, IndexArray ia) {
		VertArray_ = va;
		IndArray_ = ia;
	}

	Mesh::~Mesh() {
	}
}