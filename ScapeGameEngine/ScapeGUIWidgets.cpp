#include "ScapeGUIWidgets.h"

namespace sgeui {
	Window::Window(){
	}

	int bannerHeight = 50;

	sgeui::Window::Window(int w, int h, int xPos, int yPos) {
		w_ = w;
		h_ = h;
		x_ = xPos;
		y_ = yPos;
		render_ = false;	//This is just a container, not a RenderableQuad object

		windows.push_back(this);

		Point2D bl = { { (float)xPos / windW }, { (float)(yPos - h) / windH } };
		Point2D ur = { { (float)(xPos + w) / windW }, { (float)yPos / windH } };
		Point2D bannerBl = { bl.x, { (float)(yPos - bannerHeight) / windH }};

		//Generate the banner with a fixed height
		//Use the upper half of the texture
		RenderableQuad* banner = new RenderableQuad(bannerBl, ur);
		banner->setTextureIndex(defaultTheme);
		halveUVs(banner, true);

		//Generate the rest of the window
		//Use the bottom half of the texture
		RenderableQuad* surface = new RenderableQuad(bl, ur);
		surface->setTextureIndex(defaultTheme);
		halveUVs(surface, false);

		//Make the Window Helper
		WindowHelper* wh = new WindowHelper(bannerBl, ur);

		//Add them sorted by depth (no depth testing, remember)
		addChild(surface);
		addChild(banner);
		addChild(wh);
	}

	Window::~Window(){
		//Remove this from the windows list
		windows.remove(this);

		for (auto child : children) {
			delete child;
		}
	}

	///////////////////////////////////

	const int closeButtonTextureIndex = 3;

	WindowHelper::WindowHelper(Point2D bl, Point2D ur) {
		render_ = false;	//This is just a container, not a RenderableQuadobject

		//The close button is in the top right
		Point2D closeBl = { { ur.x - (float)(bannerHeight / 2) / windW}, { bl.y + (float)(bannerHeight / 2) / windW } };
		RenderableQuad* closeButton = new RenderableQuad(closeBl, ur);
		
		closeButton->setTextureIndex(closeButtonTextureIndex);
		closeButton->setPacked(true);
		closeButton->setBounds(closeBl, ur);
		addChild(closeButton);
	}

	void WindowHelper::update() {
		//Update the UVs based on state
		//DEBUG: just set it to texture #0
		auto UVs = packedTextures[closeButtonTextureIndex]->unpackTexture(sge::PackedTextureType::NORMAL);
		children[0]->setUVBounds({UVs[0].x, UVs[0].y}, { UVs[1].x, UVs[1].y });
	}
}