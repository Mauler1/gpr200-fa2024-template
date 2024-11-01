#version 330 core
out vec4 FragColor;

in vec2 TexPos;
in vec3 Normal;

uniform float uTime;
uniform sampler2D tex;
void main()
{
    vec4 texColor = texture(tex, TexPos);
    if(texColor.a < 0.1){
        discard;
    }
    vec3 normal = normalize(Normal);
    FragColor = texColor;
} 