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

		//Search for obj in objectList and remove
		//the first reference to it.
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
		//Bind common buffers
		//For now, just use the static VAO
		glBindVertexArray(BufferManager::VAO(VAOType::STATIC));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferManager::EAB());
		//Other buffers are bound when used
	}

	void clearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//(0, 0, 0, 1) - opaque black
		glClearColor(0, 0, 0, 1);
	}

	void initAttribPtrs() {
		//Enable the first vertex attribute array (0) that
		//stores vertex locations.
		glEnableVertexAttribArray(0);
		//The second one stores texture UV vertices
		glEnableVertexAttribArray(1);

		//Describe the first attribute array
		glBindBuffer(GL_ARRAY_BUFFER, BufferManager::VBO(VBOType::VERTEX));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//See the OpenGL documentation for explanation, but basically
		//0 - index, 3 - how many coordinates per vertex, GL_FLOAT - we're using floats
		//GL_FALSE - the data is not normalized or anything, 0 - no space between vertices,
		//(void*)0 offset to the first vertex; our data starts from the beginning, so 0

		glBindBuffer(GL_ARRAY_BUFFER, BufferManager::VBO(VBOType::UV));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Texture UV vertices have only two coordinates
	}

	//Everything necessary for starting a new frame
	void startDrawing(std::deque<Object*> objectList) {
		drawQueue = std::queue<Object*>(objectList);

		bindBuffers();
		initAttribPtrs();
	}

	void drawNext() {
		drawQueue.front()->render();

		drawQueue.pop();
	}

	void finalizeFrame(GLFWwindow* window) {
		glfwSwapBuffers(window);
		clearScreen();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
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

		//Initialize various libraries
		ilInit();
		iluInit();
		ilutInit();

		//Internal managers
		TextureManager::init();
		IOManager::init();
		GLFWIOManager::init(wind_);

		glEnable(GL_DEPTH_TEST);
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