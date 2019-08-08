#include "SGE.h"

#include "FPSCamera.h"

//This is just a simple integration test
//Of course, we can't define main when creating a
//static library
#ifndef SGE_MAKE_LIBRARY
int main() {
#else
void mainTest() {
#endif
	sge::Renderer::init(1800, 1200, "A SGE Test", false);

	auto palletMesh = sge::Mesh(".\\models\\pallet.obj");

	sge::StaticObject pallet(palletMesh);
	sge::StaticObject pallet2(palletMesh);
	sge::StaticObject pallet3(palletMesh);
	sge::StaticObject pallet4(palletMesh);

	pallet2.setPos(0, 0.18, 0);
	pallet2.setRot(0, 30, 0);

	pallet3.setPos(0, 0.37, 0);

	pallet4.setPos(0, 0.54, 0);
	pallet4.setRot(0, -25, 0);

	sge::VertexShader vs(fs::path(".\\shaders\\vs.shader"));
	sge::FragmentShader fs(fs::path(".\\shaders\\fs.shader"));
	sge::ShaderProgram prog({ vs, fs });
	sge::ShaderManager::setActive(prog);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	pallet.setTexture(woodtex);
	pallet2.setTexture(woodtex);
	pallet3.setTexture(woodtex);
	pallet4.setTexture(woodtex);

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	auto aW = new sgeui::Window(250, 250, 150, 10);
	auto bW = new sgeui::Window(350, 400, 500, 100);
	
	//auto snap = new sgeui::WindowSnapArea({ -1, -1 }, { -0.5, -0.5 }, 500, 500, 0, 0);

	//sge::FPSCamera::enable();
	//sge::FPSCamera::speed = 0.01f;

	while (true) {
		sge::Renderer::renderFrame();
	}

	return 0;
}