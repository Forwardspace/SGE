#include "SGE.h"

#include "FPSCamera.h"

//This is just a simple integration test
//Of course, we can't define main when creating a
//static library

void offsetInstance(sge::StaticObjectInstance& inst) {
	static int posY = 40;

	inst.setPos(0, posY, 0);
	inst.setRot(rand(), rand(), rand());

	//Set up the rigid body
	inst.setRigidBody(8);

	posY += 1;
}

#ifndef SGE_MAKE_LIBRARY
int main() {
#else
void mainTest() {
#endif
	//TODO: document why I'm multiplying by 0.5 times the scale in setRigidBody
	
	sge::Renderer::init(1800, 1200, "A SGE Test", false);

	auto palletMesh = sge::Mesh(".\\models\\pallet.obj");

	sge::Camera maincam({ 3, -5, 0 }, { 0, 0, 0 }, { 1, 1, 1 });
	sge::Renderer::setCurrentCamera(&maincam);

	sge::StaticObject pallet(palletMesh);
	pallet.setPos(0, 20, 0);
	pallet.setRot(90, 0, 0);
	pallet.setRigidBody(8);

	sge::InstancedStaticObject aLotOfPallets(palletMesh, 100, offsetInstance, true);

	sge::StaticObject hugePallet(palletMesh);
	hugePallet.setScl(10, 10, 10);
	hugePallet.setRigidBody(0);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	sge::Material woodMaterial {
		{&woodtex, "diffuse"}
	};
	pallet.setMaterial(&woodMaterial);
	aLotOfPallets.setMaterial(&woodMaterial);
	hugePallet.setMaterial(&woodMaterial);

	sge::SkyboxTexture clouds(".\\textures\\miramar\\miramar.tga");
	sge::Renderer::setCurrentSkyboxTex(&clouds);

	sge::FPSCameraController::enable();
	//sge::FPSCameraController::speed = 2.f;

	while (true) {
		sge::Renderer::renderFrame();
	}

	return 0;
}