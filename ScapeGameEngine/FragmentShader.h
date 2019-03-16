#pragma once
#include "stdheaders.h"
#include "Shader.h"

namespace sge {
	class FragmentShader : public Shader {
	public:
		FragmentShader();
		FragmentShader(std::string filename);
		~FragmentShader();
	};
}