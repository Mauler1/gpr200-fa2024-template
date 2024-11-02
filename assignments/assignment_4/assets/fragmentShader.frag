#version 330 core
out vec4 FragColor;

in vec2 TexPos;
in vec3 FragPos;
in vec3 Normal;

uniform float uTime;
uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;

void main()
{
    vec4 texColor = texture(tex, TexPos);
    if(texColor.a < 0.1){
        discard;
    }
    vec3 normal = normalize(Normal);
    //light direction
    vec3 lightDir = normalize(lightPos - FragPos);
    //light diffuse calculations
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    //ambient lighting
    vec3 ambient = ambientStrength * lightColor;
    //return lighting values
    vec3 result = (ambient + diffuse);
    FragColor = (texColor * vec4(result, 1.0));
} 