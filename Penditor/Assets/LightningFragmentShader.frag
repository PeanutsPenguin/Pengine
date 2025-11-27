#version 330 core
out vec4 FragColor;
  
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos;  
in vec3 Normal;

  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D tex;

vec3 specularLight()
{    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return light.specular * (spec * material.specular);  
}

vec3 diffuseLight()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    return light.diffuse * (diff * material.diffuse);;
}

vec3 ambientLight()
{
    return light.ambient * material.ambient;
}

void main()
{
    vec3 result = ambientLight() + diffuseLight() + specularLight();
    FragColor = vec4(result, 1.0);
}