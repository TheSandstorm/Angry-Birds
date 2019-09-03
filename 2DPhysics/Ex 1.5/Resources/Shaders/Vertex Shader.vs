#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

void main(void) {
	gl_Position = vec4(
		(position.x / 400.0f) - 1.0f,
		((position.y / 400.0f) - 1.0f) * -1.0f,
		position.z,
		1.0f);
	fragColor = color;
}