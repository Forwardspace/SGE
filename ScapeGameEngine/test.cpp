#include "SGE.h"

//This is just a simple integration test
//Of course, we can't define main when creating a
//static library
#ifndef SGE_MAKE_LIBRARY
int main() {
#else
void mainTest() {
#endif
	sge::Renderer::init(1024, 768, "A SGE Test", false);

	sge::StaticObject pallet(".\\models\\pallet.obj");
	sge::Renderer::registerObject(pallet);

	sge::VertexShader vs(".\\shaders\\vs.shader");
	sge::FragmentShader fs(".\\shaders\\fs.shader");
	sge::ShaderProgram prog({vs, fs});
	sge::ShaderManager::setActive(prog);

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	float x = 1;

	while (true) {
		sge::Renderer::renderFrame();

		maincam.setRot(0, 180, 0);
		pallet.setRot(0, -x / 2, 0);
		x += 0.01;
	}
}