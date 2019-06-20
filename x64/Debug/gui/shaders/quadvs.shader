#version 410 core

//Takes in 2D coordinates,
//renders triangulated quads

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 UV;

uniform mat4 translate;

out vec2 interUV;

void main() {
	interUV = UV;
	gl_Position = translate * vec4(pos, 0, 1);
}