#version 410 core

layout (location = 0) in vec3 position;
out vec3 texcoordsInterp;

uniform mat4 VPmat;

void main() {
    texcoordsInterp = position;

    gl_Position = VPmat * vec4(position, 1.0);
}