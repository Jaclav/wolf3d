#version 330

layout(location = 0) in vec3 position;
out vec3 coord;
uniform mat4 transformation;

void main() {
	coord = position;
	gl_Position = transformation * vec4(position, 1);
}