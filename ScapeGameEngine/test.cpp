#include "SGE.h"
#include "test.h"

int main() {
	sge::Renderer::init(1024, 768, "A SGE Test", false);

	sge::VertexArray va = { {-1, -1, 0}, {1, -1, 0}, {0, 1, 0} };
	sge::IndexArray ia = { 0, 1, 2 };
	sge::TexCoordArray ta = { {0, 0}, {1, 0}, {0.5, 1} };

	sge::Mesh trimesh(va, ia, ta);

	sge::StaticObject triangle(trimesh);
	sge::StaticObject otherTriangle(trimesh);

	sge::Renderer::registerObject(triangle);
	sge::Renderer::registerObject(otherTriangle);

	otherTriangle.setPos(1.5, 0, 0);

	sge::VertexShader vs(".\\shaders\\vs.shader");
	sge::FragmentShader fs(".\\shaders\\fs.shader");
	sge::ShaderProgram prog({vs, fs});
	sge::ShaderManager::setActive(prog);

	sge::Camera maincam(0, 0, 1);
	sge::Renderer::setCurrentCamera(&maincam);

	//sge::Texture groundTex(".\\textures\\default.png");
	//triangle.setTexture(groundTex);
	//No need to load the default texture

	float x = 1;

	while (true) {
		sge::Renderer::renderFrame();

		maincam.setPos(0, 0, x);
		maincam.setRot(0, 100 + x * 20, 0);
		triangle.setRot(0, -x * 2, 0);
		x += 0.01;
	}
}