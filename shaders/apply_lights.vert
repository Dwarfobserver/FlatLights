
#version 430 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inLightShift;
layout(location = 2) in uint lightId;

out vec2 argPosition;
out vec2 argLightShift;
flat out uint argLightId;

void main() {
	gl_Position = vec4(inPosition.x, inPosition.y, 0.0, 1.0);

	argPosition = gl_Position;
	argLightShift = inLightShift;
	argLightId = lightId;
}
