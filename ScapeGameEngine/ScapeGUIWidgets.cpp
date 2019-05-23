#include "ScapeGUIWidgets.h"

namespace sgeui {
	Window::Window(){
	}

	int bannerHeight = 10;

	sgeui::Window::Window(int w, int h, int xPos, int yPos) {
		w_ = w;
		h_ = h;
		x_ = xPos;
		y_ = yPos;
		render_ = false;	//This is just a container, not a renderable object

		//Generate the banner with a fixed height
		//Use the upper half of the texture
		Point2D blBanner = { { (float)xPos / windW }, { (float)(yPos - bannerHeight) / windH } };
		Point2D urBanner = { { (float)(xPos + w_) / windW }, { (float)h_ / windH } };
		
		Renderable* banner = new Renderable(rectFromTwoPoints(blBanner, urBanner));
		banner->setTx(textures[TextureType::BACKGROUND]);
		halveUVs(banner, true);
		addChild(banner);

		//Generate the rest of the window
		//Use the bottom half of the texture
		Point2D blSurface = { { (float)xPos / windW }, { (float)(yPos + h_) / windH } };
		Point2D urSurface = { { (float)(xPos + w_) / windW }, { (float)(h_ - bannerHeight) / windH } };
		
		Renderable* surface = new Renderable(rectFromTwoPoints(blSurface, urSurface));
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