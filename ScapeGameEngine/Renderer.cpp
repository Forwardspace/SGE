#include "Renderer.h"

namespace sge {
	int Renderer::w_;
	int Renderer::h_;

	glm::mat4x4 Renderer::projectionMatrix_;

	long unsigned int Renderer::frameNum_ = 0;
	GLFWwindow* Renderer::wind_ = nullptr;
	Camera* Renderer::currentCamera_;

	///////////////////
	///// Objects /////
	///////////////////

	void Renderer::registerObject(Object& obj) {
		objectList_.push_back(&obj);
	}

	void Renderer::removeObject(Object& obj) {
		int index = 0;

		for (int i = 0; i < objectList_.size(); i++) {
			if (objectList_[i] == &obj) {
				index = i;
			}
		}

		objectList_.erase(objectList_.begin() + index);
	}

	///////////////////
	///// Drawing /////
	///////////////////

	std::deque<Object*> Renderer::objectList_;

	std::queue<Object*> drawQueue;

	void bindBuffers() {
		//Bind ALL the buffers
		//For now, just use the static VAO
		glBindVertexArray(BufferManager::VAO(VAOType::STATIC));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferManager::EAB());
		glBindBuffer(GL_ARRAY_BUFFER, BufferManager::VBO());
	}

	void clearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//(0, 0, 0, 1) - opaque black
		glClearColor(0, 0, 0, 1);
	}

	//Everything necessary for starting a new frame
	void startDrawing(std::deque<Object*> objectList) {
		drawQueue = std::queue<Object*>(objectList);

		clearScreen();

		bindBuffers();

		//Enable the first vertex attribute array (0) that
		//stores vertex locations.
		glEnableVertexAttribArray(0);

		//Describe the first attribute array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//See the OpenGL documentation for explanation, but basically
		//0 - index, 3 - how many coordinates per vertex, GL_FLOAT - we're using floats
		//GL_FALSE - the data is not normalized or anything, 0 - no space between vertices,
		//(void*)0 offset to the first vertex; our data starts from the beginning, so 0

		//Other Attributes are optional, so handle them somewhere else, for now it's not implemented
	}

	void drawNext() {
		drawQueue.front()->render();

		drawQueue.pop();
	}

	void finalizeFrame(GLFWwindow* window) {
		glfwSwapBuffers(window);

		glDisableVertexAttribArray(0);
	}

	void Renderer::renderFrame() {
		callBack();

		startDrawing(objectList_);

		//Draw all registered Objects
		while (drawQueue.size()) {
			drawNext();
		}

		finalizeFrame(wind_);
	}

	void Renderer::updateProjectionMatrix(float FoV, float NCP, float FCP) {
		projectionMatrix_ = glm::perspective(glm::radians(FoV), float(w_) / float(h_), NCP, FCP);
	}

	///////////////////
	/////Callbacks/////
	///////////////////

	std::list<std::function<void()>> Renderer::windowPeriodicCallbacks_ = {};

	void Renderer::init(int w, int h, std::string name, bool fullscreen = false) {
		w_ = w; h_ = h;

		glewExperimental = true;

		if (!glfwInit()) {
			std::runtime_error up("GLFW Can't init. What now?");
			throw up;
		}

		glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

		glfwMakeContextCurrent(wind_);

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cout << glewGetErrorString(error);
			throw std::runtime_error("Unable to init GLEW! Time for some duct tape... ");
		}

		//Projection matrix is inited here with some defaults
		updateProjectionMatrix(85, 0.1f, 100);
	}

	[[ noreturn ]] void Renderer::terminate() {
		glfwTerminate();
		std::exit(0);
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

		if (glfwGetKey(Renderer::wind(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Renderer::wind())) {
			Renderer::terminate();
		}
	}
}