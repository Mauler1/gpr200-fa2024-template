#version 330 core
out vec4 FragColor;
in vec4 Color;
uniform float uTime;
uniform vec4 uColor = vec4(1.0);
void main()
{
    FragColor = Color  * (sin(uTime) * 0.5 + 0.5);
} 