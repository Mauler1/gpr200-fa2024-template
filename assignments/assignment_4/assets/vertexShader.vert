#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;
layout (location = 2) in vec3 aNormal;

out vec2 TexPos;
out vec3 Normal;

uniform float uTime;
uniform mat4 _Model;
uniform mat4 _View;
uniform mat4 _Projection;

void main()
{
    TexPos = aTexPos; //pass-through
	Normal = aNormal;
    gl_Position = _Projection * _View * _Model * vec4(aPos, 1.0);
}