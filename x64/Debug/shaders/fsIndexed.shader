#version 410 core

//Fresh from the vertex shader
in vec2 interUV;

//RGBA
out vec4 color;

uniform sampler2D diffuse;

void main() {
	color = texture(diffuse, interUV).rgba;
}