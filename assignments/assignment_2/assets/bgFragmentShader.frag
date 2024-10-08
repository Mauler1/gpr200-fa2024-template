#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float uTime;
uniform vec4 uColor = vec4(1.0);
uniform sampler2D tex;

void main()
{
    vec2 uv = 2.0 * TexCoord;
    for(float i = 1.0; i < 6.0; i++){
        uv.y += i * 0.1 / i * sin(uv.x * i * i + uTime * 0.5) * sin(uv.y * i * i + uTime * 0.5);
        uv.y += sin(uTime * i);
        uv.x += cos(uTime * i);
    }
    vec4 texColor = texture(tex, TexCoord*8);

    for(float i = 1.0; i < 8.0; i++){
        texColor = texture(tex, TexCoord * uv * 10 + uTime);
    }
    
    //texColor.r = uv.y - 0.1;
    //texColor.g = uv.y + 0.3;
    //texColor.b = uv.y + 0.95;

    //https://www.shadertoy.com/view/3ttSzr
    
    FragColor = texColor;
} 