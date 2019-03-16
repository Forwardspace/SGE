#pragma once
#include "stdheaders.h"
#include "Shader.h"

namespace sge {
	class VertexShader : public Shader {
	public:
		VertexShader();
		VertexShader(std::string filename);
		~VertexShader();
	};
}