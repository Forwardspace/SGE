#include "SGE.h"

int main() {
	sge::Renderer::init(1024, 768, "A SGE Test", false);

	sge::VertexArray va = { {1, 0, 0}, {0.5, 0, 0}, {1, 1, 0} };
	sge::IndexArray ia = { 0, 1, 2 };
	sge::Mesh trimesh(va, ia);

	sge::StaticObject triangle(trimesh);

	while (true) {
		sge::Renderer::renderFrame();
	}
}