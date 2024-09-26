#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float uTime;
uniform vec4 uColor = vec4(1.0);
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, TexCoord);
    if(texColor.a < 0.1){
        discard;
    }
    FragColor = texColor;
} 