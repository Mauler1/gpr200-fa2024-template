#version 330 core
out vec4 FragColor;

in vec2 TexPos;
in vec3 FragPos;
in vec3 Normal;

uniform float uTime;
uniform float diffuseK;
uniform float specularK;
uniform float shininess;
uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
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
    float diff = max(dot(normal, lightDir), diffuseK);
    vec3 diffuse = diff * lightColor;
    //ambient lighting
    vec3 ambient = ambientStrength * lightColor;
    //specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularK * spec * lightColor;
    //return lighting values
    vec3 result = (ambient + diffuse + specular);
    FragColor = (texColor * vec4(result, 1.0));
} 