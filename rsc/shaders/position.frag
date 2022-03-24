#version 330

in vec3 coord;
out vec4 color;

void main() {
	color = vec4(coord, 1);
}