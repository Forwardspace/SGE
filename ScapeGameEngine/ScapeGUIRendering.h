#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"

namespace sgeui {
	extern int w, h;

	struct Point2D {
		float x = 0, y = 0;
	};

	struct TexCol {
		GLbyte r = 0, g = 0, b = 0, a = 0;
	};

	using PointArray = std::vector<Point2D>;
	using IndexArray = std::vector<GLuint>;
	using UVArray = PointArray;

	class Renderable {
	public:
		Renderable(PointArray pa, IndexArray ia, UVArray ua) { pa_ = pa; ia_ = ia; ua_ = ua; }
		Renderable() {}

		void setPos(float x, float y) { x_ = x; y_ = y; }
		glm::vec2 getPos() { return glm::vec2(x_, y_); }

		void addChild(Renderable& c);
		void removeChild(Renderable& c);

		Renderable* getParent() { return parent; }

		void render();
	private:
		PointArray pa_;
		IndexArray ia_;
		UVArray ua_;

		sge::Texture tx_ = *sge::TextureManager::defaultTexture;

		std::vector<Renderable*> children;
		Renderable* parent = nullptr;

		float x_ = 0, y_ = 0;
	};

	void renderPoly(
		PointArray& pa,
		IndexArray& ia,
		UVArray& ua,
		sge::Texture& tx,
		float xP,
		float yP
	);
}