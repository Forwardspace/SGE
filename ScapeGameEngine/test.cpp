#include "SGE.h"

//This is just a simple integration test
//Of course, we can't define main when creating a
//static library
#ifndef SGE_MAKE_LIBRARY
int main() {
#else
void mainTest() {
#endif
	sge::Renderer::init(1200, 1000, "A SGE Test", false);

	sge::StaticObject pallet(".\\models\\pallet.obj");
	sge::StaticObject pallet2(".\\models\\pallet.obj");
	sge::Renderer::registerObject(pallet);
	sge::Renderer::registerObject(pallet2);

	pallet2.setPos(0, 0.18, 0);
	pallet2.setRot(0, 30, 0);

	sge::VertexShader vs(fs::path(".\\shaders\\vs.shader"));
	sge::FragmentShader fs(fs::path(".\\shaders\\fs.shader"));
	sge::ShaderProgram prog({ vs, fs });
	sge::ShaderManager::setActive(prog);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	pallet.setTexture(woodtex);
	pallet2.setTexture(woodtex);

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	auto aW = new sgeui::Window(400, 400, 10, 10);
	auto bW = new sgeui::Window(350, 400, 500, 500);

	//sge::FPSCamera::enable();
	//sge::FPSCamera::speed = 0.01f;

	float x = 1;

	while (true) {
		sge::Renderer::renderFrame();

		x += 0.01;
	}
}