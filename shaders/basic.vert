
#version 430 core

uniform vec2 uViewport;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 argPosition;
out vec2 argTexCoord;

void main() {
	gl_Position = vec4((inPosition.xy / uViewport) * 2.0 - 0.4, 0.0, 1.0);
	argPosition = gl_Position.xy;
	argTexCoord = inTexCoord;
}
