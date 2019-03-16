#pragma once
#include "stdheaders.h"
#include "IOManager.h"

namespace sge {
	//A base class for all shaders
	class Shader {
	public:
		Shader();
		//Load GLSL from file
		Shader(std::string filename);
		~Shader();
	
	protected:
		//Used by child classes only
		void shaderFromFile(GLenum type, std::string filename);

		GLuint handle = NULL;
	};
}