
#version 430 core

uniform sampler2D uTexture;

in vec2 argTexCoord;

out vec4 outColor;

void main() {
	outColor = texture(uTexture, argTexCoord);
}
