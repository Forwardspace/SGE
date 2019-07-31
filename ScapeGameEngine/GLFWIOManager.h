#pragma once
#include "stdheaders.h"

namespace sgeui {
	extern void onMousePosUpdate(int posX, int posY);
	extern void onMouseButtonUpdate(int button, bool pressed);
	extern int defaultInteractMouseButton;
}

namespace sge {
	class GLFWIOManager {
	public:
		GLFWIOManager() = delete;	//Singleton
		~GLFWIOManager() = delete;

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charCallback(GLFWwindow* window, GLuint codepoint);
		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		//Sets up all GLFW callbacks
		static void init(GLFWwindow* wind);

		//Getters
		static int mouseX() { return mouseX_; }
		static int mouseY() { return mouseY_; }
		static bool mouseKeyStatus(int n) { return mouseKeyStatus_[n]; }
		static bool isPressed(int key) { return keyStatus_[key]; }

		static std::wstring textBuffer() { return textBuffer_; }
		
		//Stores text from GLFW if true, erases the
		//text and doesn't store it if false
		static void setStoreText(bool store) {
			storeText_ = store; 
			if (!store) {
				textBuffer_ = L"";
			}
		}

	private:
		//Determines if the text recieved from GLFW is to be stored
		//in the buffer below
		static bool storeText_;
		static std::wstring textBuffer_;

		//Mouse stuff
		static int mouseX_, mouseY_;
		//Stores true if the mouse key at some location is pressed
		static std::array<bool, 8> mouseKeyStatus_;
		//Stores true if the key at some location is pressed
		static std::map<int, bool> keyStatus_;
		//Recieved from Renderer.h
		//static GLFWwindow* wind_;
	};
}