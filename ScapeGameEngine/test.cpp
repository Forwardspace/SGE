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

	float x = 1;

	double prevX = 0;
	double prevY = 0;
	while (true) {
		sge::Renderer::renderFrame();

		//TEST - showcase a simple free look camera controller
		glfwSetInputMode(sge::Renderer::wind(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double mouseSensitivity = 5;
		double speed = 0.1;

		double mY = sge::GLFWIOManager::mouseX();
		double deltaY = mY - prevY;
		deltaY *= (1 / mouseSensitivity);

		double mX = sge::GLFWIOManager::mouseY();
		double deltaX = mX - prevX;
		deltaX *= (1 / mouseSensitivity);

		bool pressedW = sge::GLFWIOManager::isPressed(GLFW_KEY_W);
		bool pressedS = sge::GLFWIOManager::isPressed(GLFW_KEY_S);
		bool pressedD = sge::GLFWIOManager::isPressed(GLFW_KEY_D);
		bool pressedA = sge::GLFWIOManager::isPressed(GLFW_KEY_A);
		float velZ = speed * pressedW - speed * pressedS;
		float velX = speed * pressedD - speed * pressedA;

		maincam.setRot(180 - deltaX, -deltaY, 0);

		//Calculate where to move to based on the camera's
		//orientation
		glm::vec3 pos = maincam.pos();
		glm::mat4 view = maincam.viewMatrix();

		glm::vec3 forward = glm::vec3(view[0][2], view[1][2], view[2][2]);
		glm::vec3 right = glm::vec3(view[0][0], view[1][0], view[2][0]);
		
		glm::vec3 deltaPosZ = forward * velZ;
		glm::vec3 deltaPosX = right * velX;

		glm::vec3 deltaPos = deltaPosX - deltaPosZ;
		pos += deltaPos;

		maincam.setPos(pos.x, pos.y, pos.z);

		x += 0.01;
	}
}