#version 330

out vec4 color;

in vec2 textureCoord;
uniform sampler2D texture2D;

void main() {
	color = texture(texture2D, textureCoord);
}