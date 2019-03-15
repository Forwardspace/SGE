#include "SGE.h"

int main() {
	auto a = glGetError();
	sge::Renderer::init(1024, 768, "A SGE Test", false);
	a = glGetError();
	while (true) {
		sge::Renderer::renderFrame();
	}
}