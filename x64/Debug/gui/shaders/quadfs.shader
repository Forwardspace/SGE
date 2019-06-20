#version 410 core

//Takes in 2D coordinates,
//renders triangulated quads

uniform sampler2D DefSampler;
in vec2 interUV;

out vec4 col;

void main() {
	col = texture(DefSampler, interUV);
}