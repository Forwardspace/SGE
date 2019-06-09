#pragma once
#include "stdheaders.h"
#include "Texture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BufferManager.h"

#include "ScapeGUITypes.h"
#include "ScapeGUIInit.h"

namespace sgeui {
	class RenderableQuad {
	public:
		RenderableQuad(Point2D bl, Point2D ur) { blBound_ = bl; urBound_ = ur; }
		RenderableQuad() {}

		void setPos(int x, int y) { x_ = x; y_ = y; }
		glm::vec2 getPos() { return glm::vec2(x_, y_); }

		void setTextureIndex(int index) { textureIndex_ = index; }
		void setPacked(bool packed) { packedTexture_ = packed; }

		Point2D bl() { return blBound_; }
		Point2D ur() { return urBound_; }

		void addChild(RenderableQuad* c);
		void removeChild(RenderableQuad* c);

		RenderableQuad* getParent() { return parent; }

		void render();
		virtual void update() {}
		void moveBy(int x, int y);

		int textureIndex() { return textureIndex_; }

		void setBounds(Point2D bl, Point2D ur) { blBound_ = bl; urBound_ = ur; }
		void setUVBounds(Point2D bl, Point2D ur) { UVblBound_ = bl, UVurBound_ = ur; }
	
		//These variables are primarily externally used
		bool awaitingButtonRelease = false;
		bool draggable = false;
		bool focused = true;
	protected:
		int textureIndex_ = defaultTheme;
		bool packedTexture_ = false;

		bool render_ = true;

		std::vector<RenderableQuad*> children;
		RenderableQuad* parent = nullptr;

		int x_ = 0, y_ = 0;
		//Bottom left and upper right bounds
		Point2D blBound_ = {0, 0}, urBound_ = {1, 1};
		Point2D UVblBound_ = {0, 0}, UVurBound_ = {1, 1};
	};

	void renderQuad(
		Point2D bl,
		Point2D ur,
		Point2D UVbl,
		Point2D UVur,
		sge::Texture* tx,
		int xP,
		int yP
	);

	void halveUVs(RenderableQuad* r, bool upper = false);
}