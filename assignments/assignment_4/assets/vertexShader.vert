#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; //Varying
uniform float uTime;
uniform mat4 _Model;

void main()
{
	Color = aColor; //pass-through
	//vec4 pos = vec4(aPos, 1.0);
	//mat4 M = translate(1.0, 2.0, 1.5) * rotateZ(radians(uTime * 90.0)) * scale(2.0, 1.0, 1.0);
	//pos = M * pos;
    gl_Position = _Model * vec4(apos, 1.0);
}