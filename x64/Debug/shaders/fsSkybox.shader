#version 410 core

in vec3 texcoordsInterp;
out vec4 colour;

uniform samplerCube diffuse;

void main() {
    colour = texture(diffuse, texcoordsInterp);
}