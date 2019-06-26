#include "ScapeGUIWindowWidgets.h"

#include "ScapeGUIMouseState.h"

#include "PackedTexture.h"
#include "UserInputManager.h"

namespace sgeui {
	Window::Window() {
	}

	int bannerHeight = 50;

	sgeui::Window::Window(int w, int h, int xPos, int yPos) {
		w_ = w;
		h_ = h;
		x_ = xPos;
		y_ = yPos;
		renderRenderable = false;	//This is just a container, not a real object

		windows.push_back(this);

		Point2D bl = { { (float)xPos / windW }, { (float)(yPos - h) / windH } };
		Point2D ur = { { (float)(xPos + w) / windW }, { (float)yPos / windH } };
		Point2D bannerBl = { bl.x, { (float)(yPos - bannerHeight) / windH }};

		//Set the bl and ur bound to aid with collision detection
		blBound_ = bl;
		urBound_ = ur;

		//Generate the banner with a fixed height
		//Use the upper half of the texture
		WindowBanner* banner = new WindowBanner(bannerBl, ur);
		banner->setTextureIndex(defaultTheme);
		halveUVs(banner, true);

		//Generate the rest of the window
		//Use the bottom half of the texture
		RenderableQuad* surface = new RenderableQuad(bl, { ur.x, bannerBl.y });
		surface->setTextureIndex(defaultTheme);
		halveUVs(surface, false);

		//Make the Window Helper
		WindowHelper* wh = new WindowHelper(bannerBl, ur);

		//Add them sorted by depth (no depth testing, remember)
		addChild(banner);
		addChild(surface);
		addChild(wh);
	}

	Window::~Window(){
		//Remove this from the windows list
		windows.erase(std::remove(windows.begin(), windows.end(), this), windows.end());

		for (auto child : children) {
			delete child;
		}
	}

	void Window::setSize(int w, int h) {
		float fracX = (float)w / windW;
		float fracY = (float)h / windH;

		urBound_.x = blBound_.x + fracX;
		urBound_.y = blBound_.y + fracY;

		h_ = h;
		w_ = w;

		//Update the size of the surface (fracX, fracY - bannerHeight)
		auto blBound = children[1]->bl();
		children[1]->setBounds(blBound, { blBound.x + fracX, blBound.y + fracY - (float)bannerHeight / windH });

		//Relocate the banner and WindowHelper
		int dX = w_ - w;
		int dY = h_ - h;

		//Relocate the banner
		children[0]->moveBy(dX, dY);

		//Relocate the window helper
		children[2]->moveBy(dX, dY);
	}

	///////////////////////////////////

	void WindowBanner::update() {
		ClickState::Enum state = getClickState(this);
		if (state == ClickState::CLICK_AND_DRAG) {
			//Relocate the parent Window to the mouse location
			//as long as the mouse button is held down
			//(move the Window)
			//Also, convert the GLFW coordinates to SGEUI coordinates
			parent->moveBy(mouseDeltaX * 2, -mouseDeltaY * 2);

			pushWindowOnTop(static_cast<Window*>(parent));

			focused_ = true;

			//Check if any window is below the current one
			//If so, make it unfocused to prevent mouse clicks
			for (Window* w : windows) {
				if (collide(w, parent)) {
					w->setFocused(false);
				}
			}
		}
	}

	///////////////////////////////////

	const int closeButtonTextureIndex = 3;

	WindowHelper::WindowHelper(Point2D bl, Point2D ur) {
		renderRenderable = false;	//This is just a container, not a real object


		//The close button is in the top right
		Point2D closeBl = { ur.x - (float)bannerHeight * 0.66f / windW, bl.y + (float)bannerHeight * 0.33f / windH};
		RenderableQuad* closeButton = new RenderableQuad(closeBl, ur);
		
		closeButton->setTextureIndex(closeButtonTextureIndex);
		closeButton->setPacked(true);
		closeButton->setBounds(closeBl, ur);
		addChild(closeButton);
	}

	////////////////////////////////////

	WindowSnapArea::WindowSnapArea(Point2D bl, Point2D ur, int wX, int wY, int windPosX, int windPosY) {
		blBound_ = bl;
		urBound_ = ur;
		wX_ = wX;
		wY_ = wY;
		windPosX_ = windPosX;
		windPosY_ = windPosY;

		renderRenderable = false;	//This is just a virtual object, not a real one
	}

	void WindowSnapArea::update() {
		if (draggedRenderable == nullptr) {
			if (windowInArea != nullptr) {
				//Either fix or revert size and pos

				if (!collide(this, windowInArea)) {
					//Revert the size and pos
					windowInArea->setSize(std::get<0>(windowPos), std::get<1>(windowPos));
					windowInArea->setSize(std::get<0>(windowSize), std::get<1>(windowSize));
				}

				//In any case, don't move or resize the Window anymore
				windowInArea = nullptr;
			}
		}
		else {
			//OK, something is being dragged,
			//check if it's a window banner
			WindowBanner* wb = dynamic_cast<WindowBanner*>(draggedRenderable);
			if (wb) {
				//Yup, get the window
				windowInArea = static_cast<Window*>(wb->getParent());

				//Display preview of size and pos before the user releases button
				windowPos = windowInArea->getPos();
				windowSize = windowInArea->getSize();

				//Replace size and pos for the preview
				windowInArea->setSize(wX_, wY_);
				windowInArea->setPos(windPosX_, windPosY_);
			}
		}
	}

	////////////////////////////////////

	std::array<glm::vec2, 2> getUVsFromState(ClickState::Enum state, sge::PackedTexture* tex) {
		if (state == ClickState::CLICKED) {
			return tex->unpackTexture(sge::PackedTextureType::RELEASED);
		}
		else if (state == ClickState::HOVER) {
			return tex->unpackTexture(sge::PackedTextureType::HOVER);
		}
		else if (state == ClickState::AWAITING_BUTTON_RELEASE) {
			return tex->unpackTexture(sge::PackedTextureType::CLICK);
		}
		else {
			//NONE
			return tex->unpackTexture(sge::PackedTextureType::NORMAL);
		}
	}

	void WindowHelper::update() {
		updateCloseButton();
	}

	bool hit(Point2D bl, Point2D ur) {
		double mX = sge::GLFWIOManager::mouseX();
		double mY = sge::GLFWIOManager::mouseY();

		//Convert top left coords (GLFW) to middle based coords (GL)
		mX = (mX / windW - 0.5) * 2;
		mY = -(mY / windH - 0.5) * 2;

		if (mX > bl.x && mX < ur.x) {
			if (mY > bl.y && mY < ur.y) {
				//We've got a hit!
				return true;
			}
		}

		return false;
	}

	bool collide(RenderableQuad* r1, RenderableQuad* r2) {
		if (r1 == r2) {
			//A window can't collide with itself
			return false;
		}

		//Check if one Window is to the left of the other
		if (r1->ur().x <= r2->bl().x || r2->ur().x <= r1->bl().x) {
			//That means they do not collide.
			return false;
		}

		//Is one on top of the other (vertically)?
		if (r1->ur().y <= r2->bl().y || r2->ur().y <= r1->bl().y) {
			//Then they also do not collide
			return false;
		}

		return true;
	}

	void pushWindowOnTop(Window* target) {
		if (windows.back() != target) {
			//Target is not on top

			Window* top = windows.back();
			auto targetLocation = std::find(windows.begin(), windows.end(), target);
			
			if (targetLocation == std::end(windows)) {
				throw std::runtime_error("Target Window* is not in windows vector! Use linux?");
			}

			targetLocation[0] = top;
			windows.back() = target;
		}
	}

	void WindowHelper::updateCloseButton() {
		//Update the UVs based on state
		sge::PackedTexture* tex = packedTextures[children[0]->textureIndex()];

		ClickState::Enum state = getClickState(children[0]);

		if (state == ClickState::CLICKED) {
			//Delete the parent window
			dynamic_cast<Window*>(parent)->~Window();
			return;
		}

		std::array<glm::vec2, 2> UVs = getUVsFromState(state, tex);
		children[0]->setUVBounds({ UVs[0].x, UVs[0].y }, { UVs[1].x, UVs[1].y });
	}
}