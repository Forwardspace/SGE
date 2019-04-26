#pragma once
#include "stdheaders.h"
#include "Object.h"
#include "BufferManager.h"
#include "TextureManager.h"
#include "Camera.h"

namespace sge {
	class Renderer {
	public:
		Renderer() = delete;	//Singleton
		~Renderer() = delete;

		static GLFWwindow* wind() { return wind_; };

		static glm::mat4x4 projectionMatrix() { return projectionMatrix_; }
		static Camera* currentCamera() { 
			if (!currentCamera_) {
				throw std::runtime_error("No Camera initialized! Mom, get the camera!"); 
			} 
			else { 
				return currentCamera_; 
			}
		}

		static void setCurrentCamera(Camera* cam) { currentCamera_ = cam; }

		//Register a new Object to be drawn on the screen
		static void registerObject(Object& obj);
		//Remove an Object from being drawn to the screen
		static void removeObject(Object& obj);

		//Initiates rendering of a new frame
		//(call this when done with the frame)
		static void renderFrame();

		static void updateProjectionMatrix(float FoV, float NCP, float FCP);

		static void registerWindowCallback(std::function<void()>);
		static void removeWindowCallback(std::function<void()>);

		static void init(int w, int h, std::string name, bool fullscreen);
		[[ noreturn ]] static void terminate();
	private:
		//A direct handle to the active GLFW window
		static GLFWwindow* wind_;

		static int w_, h_;

		///////////////////
		///// Drawing /////
		///////////////////

		static glm::mat4x4 projectionMatrix_;

		static Camera* currentCamera_;

		//Stores pointers to objects that have to be drawn each frame
		//Note that this is a list, but not a std::list
		static std::deque<Object*> objectList_;

		//The number of the current frame
		static long unsigned int frameNum_;

		///////////////////
		/////Callbacks/////
		///////////////////

		//How many calls could a callback back if
		//a callback could back calls?
		static void callBack();

		//Called every frame, these functions handle input and respond
		//to the operating system's signals
		static std::list<std::function<void()>> windowPeriodicCallbacks_;
	};

	void defaultWindowPeriodicCallback();
}