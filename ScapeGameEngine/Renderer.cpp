#include "Renderer.h"

namespace sge {
	long unsigned int Renderer::frameNum_ = 0;
	GLFWwindow* Renderer::wind_ = nullptr;

	///////////////////
	/////Callbacks/////
	///////////////////

	std::list<std::function<void()>> Renderer::windowPeriodicCallbacks_ = {};

	void Renderer::init(int w, int h, std::string name, bool fullscreen = false) {
		//glewExperimental = true;
		if (!glfwInit()) {
			std::runtime_error up("GLFW Can't init. What now?");
			throw up;
		}

		glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //New OpenGL

		wind_ = glfwCreateWindow(
			w,
			h,
			name.c_str(),
			fullscreen ? glfwGetPrimaryMonitor() : NULL,
			NULL
		);

		if (wind_ == 0) {
			throw std::runtime_error("GLFW Unable to init window! What are we (not) paying you for?");
		}

	}

	[[ noreturn ]] void Renderer::terminate() {
		glfwTerminate();
		std::exit(0);
	}

	void Renderer::renderFrame() {
		callBack();
	}

	void Renderer::registerWindowCallback(std::function<void()> callback) {
		windowPeriodicCallbacks_.push_back(callback);
	}

	void Renderer::removeWindowCallback(std::function<void()> callback) {
		windowPeriodicCallbacks_.remove_if(
			[callback](std::function<void()> toCompare) {
				return (callback.target<void()>() == toCompare.target<void()>()); 
			}
		);
	}

	void Renderer::callBack() {
		if (windowPeriodicCallbacks_.size() == 0) {
			defaultWindowPeriodicCallback();
		}
		else {
			for (auto f : windowPeriodicCallbacks_) {
				f();
			}
		}
	}

	void defaultWindowPeriodicCallback() {
		glfwPollEvents();

		if (glfwGetKey(Renderer::getWind(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Renderer::getWind())) {
			Renderer::terminate();
		}
	}
}