#include "SGE.h"

int main() {
	sge::Renderer::init(1024, 768, "A SGE Test", false);

	while (true) {
		sge::Renderer::renderFrame();
	}
}