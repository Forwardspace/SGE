#pragma once
#include "stdheaders.h"
#include "IOManager.h"

namespace sge {
	//A base class for all shaders
	class Shader {
	public:
		Shader();
		//Load GLSL from file
		Shader(fs::path filename);
		//Load GLSL from char*
		Shader(std::string data);
		~Shader();

		GLuint handle() { return handle_; }
	
	protected:
		//Used by child classes only
		void shaderFromString(GLenum type, std::string source);

		GLuint handle_ = NULL;
	};
}