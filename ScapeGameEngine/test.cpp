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

	sge::VertexShader vs(fs::path(".\\shaders\\vs.shader"));
	sge::FragmentShader fs(fs::path(".\\shaders\\fs.shader"));
	sge::ShaderProgram prog({ vs, fs });
	sge::ShaderManager::setActive(prog);

	sge::Texture woodtex(".\\textures\\woodtex.jpg");
	pallet.setTexture(woodtex);

	sge::Camera maincam(0, 0.5, 1.8);
	sge::Renderer::setCurrentCamera(&maincam);

	float x = 1;

	double prevX = 0;
	double prevY = 0;
	while (true) {
		sge::Renderer::renderFrame();

		//TEST - showcase a simple fps controller
		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double mY = sge::GLFWIOManager::mouseX();
		double deltaY = mY - prevY;
		deltaY /= 5;

		double mX = sge::GLFWIOManager::mouseY();
		double deltaX = mX - prevX;
		deltaX /= 5;

		maincam.setRot(180 - deltaX, -deltaY, 0);
		pallet.setRot(0, 180, 0);
		x += 0.01;
	}
}