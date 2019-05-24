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
		render_ = false;	//This is just a container, not a renderable object


		Point2D bl = { { (float)xPos / windW }, { (float)(yPos - h) / windH } };
		Point2D ur = { { (float)(xPos + w) / windW }, { (float)yPos / windH } };
		Point2D bannerBl = { bl.x, { (float)(yPos - bannerHeight) / windH }};

		//Generate the banner with a fixed height
		//Use the upper half of the texture
		Renderable* banner = new Renderable(rectFromTwoPoints(bannerBl, ur));
		banner->setTx(textures[TextureType::BACKGROUND]);
		halveUVs(banner, true);
		addChild(banner);

		//Generate the rest of the window
		//Use the bottom half of the texture
		Renderable* surface = new Renderable(rectFromTwoPoints(bl, ur));
		surface->setTx(textures[TextureType::BACKGROUND]);
		halveUVs(surface, false);
		addChild(surface);
	}

	Window::~Window(){
		for (auto child : children) {
			delete child;
		}
	}
}