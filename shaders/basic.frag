
#version 430 core

uniform sampler2D uTexture;
uniform sampler2D uNormalMap;

uniform vec2 uLightPosition;

in vec2 argPosition;
in vec2 argTexCoord;

out vec4 outColor;

void main() {
	vec2 diff = uLightPosition - argPosition;
	float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
	vec3 direction = normalize(vec3(diff.xy, 1.0));
	vec3 normal = texture(uNormalMap, argTexCoord).xyz;
	vec3 color = texture(uTexture, argTexCoord).xyz;
	float normalCoef = dot(direction, normal);
	outColor = vec4(color.xyz, 1.0) * normalCoef;

	if (distance < 0.01f) outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
