
#version 430 core

struct light_data {
	vec3 color;
	float strength;
};

uniform sampler2D uTexture;
uniform sampler2D uNormalMap;

uniform light_data lights[100];

in vec2 argPosition;
in vec2 argLightShift;
flat in uint argLightId;

out vec4 outColor;

void main() {
	vec4 color = texture(uTexture, argPosition);
	// ...
	outColor = color;
}
