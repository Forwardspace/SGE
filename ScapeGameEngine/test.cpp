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
		500,
		offsetInstance
	);

	sge::StaticObject pallet(palletMesh);
	pallet.setPos(0, 0, -7);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	sge::Material woodMaterial {
		{&woodtex, "diffuse"}
	};
	pallets.setMaterial(&woodMaterial);

	sge::SkyboxTexture clouds(".\\textures\\miramar\\miramar.tga");
	sge::Renderer::setCurrentSkyboxTex(&clouds);

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