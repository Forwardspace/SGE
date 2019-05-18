#pragma once

namespace sgeui {
	struct Point2D {
		float x = 0, y = 0;
	};

	struct TexCol {
		GLbyte r = 0, g = 0, b = 0, a = 0;
	};

	using PointArray = std::vector<Point2D>;
	using IndexArray = std::vector<GLuint>;
	using UVArray = PointArray;

	class Renderable;
}