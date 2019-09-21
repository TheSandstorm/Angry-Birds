#version 430 core

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;
uniform sampler2D tex;

void main() {


    color = texture(tex, fragTexCoord);
    
}