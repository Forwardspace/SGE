#include "ScapeGUIWidgets.h"

namespace sgeui {
	Window::Window(){
	}

	int bannerHeight = 50;

	int defaultInteractMouseButton = GLFW_MOUSE_BUTTON_1;

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
		windows.erase(std::remove(windows.begin(), windows.end(), this), windows.end());

		for (auto child : children) {
			delete child;
		}
	}

	///////////////////////////////////

	const int closeButtonTextureIndex = 3;

	WindowHelper::WindowHelper(Point2D bl, Point2D ur) {
		render_ = false;	//This is just a container, not a RenderableQuadobject

		//The close button is in the top right
		Point2D closeBl = { ur.x - (float)bannerHeight * 0.66 / windW, bl.y + (float)bannerHeight * 0.33 / windH};
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
	
		if (clickedOn(
			children[0]->bl(),
			children[0]->ur(),
			children[0]->awaitingLMBRelease)
		) {
			dynamic_cast<Window*>(parent)->~Window();
		}
	}

	bool hit(Point2D bl, Point2D ur) {
		double mX = sge::GLFWIOManager::mouseX();
		double mY = sge::GLFWIOManager::mouseY();

		//Convert top left coords (GLFW) to middle based coords (GL)
		mX = (mX / windW - 0.5) * 2;
		mY = -(mY / windH - 0.5) * 2;

		std::cout << mX << " : " << mY << std::endl;
		std::cout << bl.x << " : " << ur.x << std::endl;
		std::cout << bl.y << " : " << ur.y << std::endl;
		std::cout << "----------" << std::endl;


		if (mX > bl.x && mX < ur.x) {
			if (mY > bl.y && mY < ur.y) {
				//We've got a hit!
				return true;
			}
		}

		return false;
	}

	bool clickedOn(Point2D bl, Point2D ur, bool& awaitingLMBRelease) {
		if (awaitingLMBRelease) {
			if (hit(bl, ur)) {
				if (!sge::GLFWIOManager::mouseKeyStatus(defaultInteractMouseButton)) {
					//The mouse button was previously pressed and, 
					//now, released
					return true;
				}
			}
		}
		else {
			if (hit(bl, ur)) {
				if (sge::GLFWIOManager::mouseKeyStatus(defaultInteractMouseButton)) {
					awaitingLMBRelease = true;
				}
			}
		}

		return false;
	}
}