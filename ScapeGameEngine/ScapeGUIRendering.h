#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BufferManager.h"

#include "ScapeGUITypes.h"

namespace sgeui {
	extern int w, h;
	extern sge::ShaderProgram GUIShaderProgram;

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

		//Get point array
		PointArray pa() { return pa_; }
		IndexArray ia() { return ia_; }
		UVArray ua() { return ua_; }
	private:
		PointArray pa_;
		IndexArray ia_;
		UVArray ua_;

		sge::Texture tx_ = *sge::TextureManager::defaultTexture;

		std::vector<Renderable*> children;
		Renderable* parent = nullptr;

		float x_ = 0, y_ = 0;
		//Bottom left and upper right bounds
		Point2D blBound, urBound;
	};

	void renderPoly(
		PointArray& pa,
		IndexArray& ia,
		UVArray& ua,
		sge::Texture& tx,
		float xP,
		float yP
	);

	Renderable rectFromTwoPoints(Point2D bl, Point2D ur);
}