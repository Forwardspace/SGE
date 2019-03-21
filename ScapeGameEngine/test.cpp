#include "SGE.h"

int main() {
	sge::Renderer::init(1024, 768, "A SGE Test", false);

	sge::VertexArray va = { {-1, -1, 0}, {1, -1, 0}, {0, 1, 0} };
	sge::IndexArray ia = { 0, 1, 2 };
	sge::Mesh trimesh(va, ia);

	sge::StaticObject triangle(trimesh);

	sge::Renderer::registerObject(triangle);

	sge::VertexShader vs("C:\\Users\\Juraj\\source\\repos\\ScapeGameEngine\\x64\\Debug\\shaders\\vs.shader");
	sge::FragmentShader fs("C:\\Users\\Juraj\\source\\repos\\ScapeGameEngine\\x64\\Debug\\shaders\\fs.shader");
	sge::ShaderProgram prog({vs, fs});

	glUseProgram(prog.handle());

	while (true) {
		sge::Renderer::renderFrame();
	}
}