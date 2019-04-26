#include "SGE.h"

int main() {
	sge::Renderer::init(1024, 768, "A SGE Test", false);
/*
	sge::VertexArray va = { {-1, -1, 0}, {1, -1, 0}, {0, 1, 0} };
	sge::IndexArray ia = { 0, 1, 2 };
	sge::TexCoordArray ta = { {0, 0}, {1, 0}, {0.5, 1} };

	sge::Mesh trimesh(va, ia, ta);*/
	//No need to manually create the meshes now

	sge::StaticObject container(".\\models\\pallet.obj");

	sge::Renderer::registerObject(container);

	sge::VertexShader vs(".\\shaders\\vs.shader");
	sge::FragmentShader fs(".\\shaders\\fs.shader");
	sge::ShaderProgram prog({vs, fs});
	sge::ShaderManager::setActive(prog);

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	float x = 1;

	while (true) {
		sge::Renderer::renderFrame();

		//maincam.setPos(0, 0, x);
		maincam.setRot(0, 180, 0);
		container.setRot(0, -x / 2, 0);
		x += 0.01;
	}
}