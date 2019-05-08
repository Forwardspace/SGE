#pragma once
#include "stdheaders.h"
#include "Shader.h"

namespace sge {
	class FragmentShader : public Shader {
	public:
		FragmentShader();
		FragmentShader(fs::path filename);
		FragmentShader(std::string source);
		~FragmentShader();
	};
}