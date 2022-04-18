#version 330

out vec4 color;

in vec2 textureCoord;
uniform sampler2D texture;

void main() {
	color = texture2D(texture, textureCoord);

	if(color.a == 0) {
		discard;
	}
}