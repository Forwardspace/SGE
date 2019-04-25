#version 410 core

//Fresh from the vertex shader
in vec2 interUV;

//RGBA
out vec4 color;

uniform sampler2D DefSampler;

void main() {
	color = texture(DefSampler, interUV).rgba;
}