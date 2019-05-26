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

		//Generate the rest of the window
		//Use the bottom half of the texture
		Renderable* surface = new Renderable(rectFromTwoPoints(bl, ur));
		surface->setTx(textures[TextureType::BACKGROUND]);
		halveUVs(surface, false);

		//Make the Window Helper
		WindowHelper* wh = new WindowHelper(ur, bannerBl);

		//Add them sorted by depth (no depth testing, remember)
		addChild(surface);
		addChild(banner);
		addChild(wh);
	}

	Window::~Window(){
		for (auto child : children) {
			delete child;
		}
	}

	///////////////////////////////////

	WindowHelper::WindowHelper(Point2D ur, Point2D bl){
		render_ = false;	//This is just a container, not a renderable object

		//The close button is in the top right
		Point2D closeBl = { { ur.x - (float)bannerHeight / windW }, { bl.y } };
		Renderable* closeButton = new Renderable(rectFromTwoPoints(closeBl, ur));
		
		//closeButton->setTx(textures[TextureType::CLOSE_BUTTON]);
		closeButton->setTx(sge::TextureManager::defaultTexture);
		closeButton->setBounds(closeBl, ur);
		addChild(closeButton);
	}
}