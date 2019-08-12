#include "SGE.h"

#include "FPSCamera.h"

//This is just a simple integration test
//Of course, we can't define main when creating a
//static library

void offsetInstance(sge::StaticObjectInstance& inst) {
	static int posX = 0;

	int currPosRow = posX % 20 + rand() * 0.005;
	int currPosColumn = posX / 20 + rand() * 0.005;

	inst.setPos(currPosRow, 0, currPosColumn);
	inst.setRot(rand(), rand(), rand());

	posX += 1;
}

#ifndef SGE_MAKE_LIBRARY
int main() {
#else
void mainTest() {
#endif
	sge::Renderer::init(1800, 1200, "A SGE Test", false);

	auto palletMesh = sge::Mesh(".\\models\\pallet.obj");

	float posX = -10;

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	sge::InstancedStaticObject pallets(
		palletMesh,
		1000,
		offsetInstance
	);

	sge::StaticObject pallet(palletMesh);
	pallet.setPos(0, 0, -3);

	//sge::StaticObject pallet(palletMesh);
	//sge::StaticObject pallet2(palletMesh);

	/*pallet2.setPos(0, 0.18, 0);
	pallet2.setRot(0, 30, 0);

	pallet3.setPos(0, 0.37, 0);

	pallet4.setPos(0, 0.54, 0);
	pallet4.setRot(0, -25, 0);*/

	sge::VertexShader vs(fs::path(".\\shaders\\vs.shader"));
	sge::FragmentShader fs(fs::path(".\\shaders\\fs.shader"));
	sge::ShaderProgram prog({ vs, fs });
	sge::ShaderManager::setActive(prog);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	pallets.setTexture(woodtex);
	/*pallet2.setTexture(woodtex);
	pallet3.setTexture(woodtex);
	pallet4.setTexture(woodtex);*/

	auto aW = new sgeui::Window(250, 250, 150, 10);
	auto bW = new sgeui::Window(350, 400, 500, 100);
	
	//auto snap = new sgeui::WindowSnapArea({ -1, -1 }, { -0.5, -0.5 }, 500, 500, 0, 0);

	sge::FPSCamera::enable();
	sge::FPSCamera::speed = 0.1f;

	while (true) {
		sge::Renderer::renderFrame();

		pallets.transformInstances([](sge::StaticObjectInstance& inst) {
			auto rot = inst.rot();
			inst.setRot(rot.x + 0.01, rot.y + 0.01, rot.z + 0.01);
		});
	}

	return 0;
}