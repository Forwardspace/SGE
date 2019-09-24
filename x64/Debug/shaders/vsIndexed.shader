#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 UV;
layout(location = 2) in mat4 MVP;

out vec2 interUV;

void main() {
	gl_Position = MVP * vec4(pos, 1);

	//Interpolate all the UVs for the fragment shader
	interUV = UV;
}