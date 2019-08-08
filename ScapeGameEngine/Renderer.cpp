#include "Renderer.h"

namespace sge {
	int Renderer::w_;
	int Renderer::h_;

	glm::mat4x4 Renderer::projectionMatrix_;

	long unsigned int Renderer::frameNum_ = 0;
	GLFWwindow* Renderer::wind_ = nullptr;
	Camera* Renderer::currentCamera_;

	double deltaTime;

	///////////////////
	///// Objects /////
	///////////////////

	void Renderer::registerObject(Object* obj) {
		objectList_.push_back(obj);
	}

	void Renderer::removeObject(Object* obj) {
		int index = 0;

		//Search for obj in objectList and remove
		//the first reference to it.
		for (int i = 0; i < objectList_.size(); i++) {
			if (objectList_[i] == obj) {
				index = i;
			}
		}

		objectList_.erase(objectList_.begin() + index);
	}

	///////////////////
	///// Drawing /////
	///////////////////

	//Calculate deltaTime each frame
	std::clock_t timer;
	void startTimer() {
		timer = std::clock();
	}

	void endTimer() {
		deltaTime = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
	}

	std::deque<Object*> Renderer::objectList_;

	std::queue<Object*> drawQueue;

	void clearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//(0, 0, 0, 1) - opaque black
		glClearColor(0, 0, 0, 1);
	}

	bool firstDraw = true;
	int previousObject = -1;

	//Everything necessary for starting a new frame
	void startDrawing(std::deque<Object*> objectList) {
		drawQueue = std::queue<Object*>(objectList);
	}

	void drawNext() {
		auto current = drawQueue.front();

		if ((int)current->type() != previousObject) {
			if (firstDraw) {
				current->setupVAO();
			}

			//Bind the correct VAO
			BufferManager::bindVAO((unsigned int)current->type());

			previousObject = (int)current->type();
		}

		current->render();

		drawQueue.pop();
	}

	void finalizeFrame(GLFWwindow* window) {
		//Update the GUI (has to be done last not to overlap with any vertices)
		sgeui::render();

		//Update the UserInputManager
		//It has to be updated last because of the
		//mouse delta calculation
		UserInputManager::update();

		glfwSwapBuffers(window);
		clearScreen();

		if (firstDraw) {
			firstDraw = false;
		}

		previousObject = -1;
	}

	void Renderer::renderFrame() {
		startDrawing(objectList_);

		//Draw all registered Objects
		while (drawQueue.size()) {
			drawNext();
		}

		finalizeFrame(wind_);

		callBack();
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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Cannot initialize Glad! I'll gladly stop.");
		}
		glGetError();	//Clear error buffer

		//Projection matrix is inited here with some defaults
		updateProjectionMatrix(85, 0.1f, 1000);

		///////////////////////////////
		/////ACTUAL INITIALIZATION/////
		///////////////////////////////

		//Initialize various libraries
		ilInit();
		iluInit();
		ilutInit();

		//Internal managers
		TextureManager::init();
		IOManager::init();
		GLFWIOManager::init(wind_);
		//GUI
		sgeui::init(sge::Renderer::wind(), w_, h_);

		windowPeriodicCallbacks_.push_back(defaultWindowPeriodicCallback);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);
	}

	[[ noreturn ]] void Renderer::terminate(bool exit) {
		//Some cleanup
		IOManager::terminate();

		glfwTerminate();

		if (exit) {
			std::exit(0);
		}
	}

	void Renderer::registerWindowCallback(std::function<void()> callback) {
		windowPeriodicCallbacks_.push_back(callback);
	}

	void Renderer::removeWindowCallback(std::function<void()> callback) {
		windowPeriodicCallbacks_.remove_if(
			[callback](std::function<void()> toCompare) {
				return (callback.target<void>() == toCompare.target<void>()); 
			}
		);
	}

	void Renderer::callBack()  {
		for (auto f : windowPeriodicCallbacks_) {
			f();
		}
	}

	void defaultWindowPeriodicCallback() {
		glfwPollEvents();

		if (glfwGetKey(Renderer::wind(), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Renderer::wind())) {
			Renderer::terminate();
		}
	}
}