#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texturePosition;
out vec2 textureCoord;

uniform mat4 transformation;

void main() {
	textureCoord = texturePosition;
	gl_Position = transformation * vec4(position, 1);
}