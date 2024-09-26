#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color; //Varying
out vec2 TexCoord;

uniform float uTime;

void main()
{
	Color = aColor; //pass-through
	TexCoord = aTexCoord;
	vec3 pos = aPos;
	pos.y += (abs(sin(uTime*3)/6));
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}