#version 430 core

in vec3 fragTexCoord;
in vec4 mWorldPos;

out vec4 color;

uniform samplerCube cubeSampler;
uniform vec3 camPos;
void main()
{
    float d = distance(mWorldPos.xyz, camPos);
    float lerp = (d - 5.0f)/10.f; 
    lerp = clamp(lerp, 0.0, 1.0);
    vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    color = texture(cubeSampler, fragTexCoord);
    color = mix(color, vFogColor, lerp);
}