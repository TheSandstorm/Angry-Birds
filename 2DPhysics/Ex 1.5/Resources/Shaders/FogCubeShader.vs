#version 450 core

layout (location = 0) in vec3 position;

out vec3 fragTexCoord;
out vec4 mWorldPos;

uniform mat4 MVP;
uniform mat4 model;

void main() 
{
	mWorldPos = model * vec4(position, 1.0); 
    gl_Position = MVP * vec4(position, 1.0);
    fragTexCoord = position;
}