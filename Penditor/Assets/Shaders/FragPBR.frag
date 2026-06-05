#version 330 core
const float PI = 3.14159265359;
const int MAXPOINTLIGHT = 10;
const int MAXSPOTLIGHT = 10;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
//in vec3 Normal;
in mat3 TBN;

struct Material
{
    vec3  albedo;
    sampler2D albedoMap;

    float metallic;
    sampler2D metallicMap;

    float roughness;
    sampler2D roughnessMap;

    float ao;
    sampler2D aoMap;

    sampler2D normalMap;
};
uniform Material mat;

uniform vec3 camPos;

uniform int numPointLight;
struct PointLight
{
    vec3 position;
    float intensity;
    vec3 color;
    float radius;
    bool enabled;
};
uniform PointLight pointLights[MAXPOINTLIGHT];

uniform int numSpotLight;
struct SpotLight
{
    vec3 position;
    float intensity;
    vec3 direction;
    float cutOff;
    vec3 color;
    float outerCutOff; 
    float radius;
    bool enabled;
};
uniform SpotLight spotLights[MAXSPOTLIGHT];

struct DirectionnalLight
{
    vec3 direction;
    float intensity;
    vec3 color;
    bool enabled;
};
uniform DirectionnalLight dirLight;



float DistributionGGX(vec3 N, vec3 H, float roughness) 
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) 
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(float NdotV, float NdotL, float roughness) 
{
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) 
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 ComputePBR(vec3 L, vec3 V, vec3 N, vec3 radiance, vec3 albedo, float metallic, float roughness, vec3 F0) 
{
    vec3 H = normalize(V + L);
    
    float NdotV = max(dot(N, V), 0.0001);
    float NdotL = max(dot(N, L), 0.0001);
    float HdotV = max(dot(H, V), 0.0);
    
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(NdotV, NdotL, roughness);   
    vec3 F    = fresnelSchlick(HdotV, F0);       
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;     
    
    vec3 numerator    = NDF * G * F;

    float denominator = 4.0 * NdotV * NdotL; 
    vec3 specular     = numerator / denominator;  
                        
    return (kD * albedo / PI + specular) * radiance * NdotL;
}

void main() 
{
    vec3 localNormal = texture(mat.normalMap, TexCoords).rgb;
    localNormal = localNormal * 2.0 - 1.0;   
    
    vec3 N = normalize(TBN * localNormal);

//    vec3 N = normalize(Normal);       <- Old School normal
    vec3 V = normalize(camPos - FragPos);


    vec3 albedo     =   texture(mat.albedoMap, TexCoords).rgb * mat.albedo;
    float roughness =   texture(mat.roughnessMap, TexCoords).r * mat.roughness;
    float metallic  =   texture(mat.metallicMap, TexCoords).r * mat.metallic;
    float ao        =   texture(mat.aoMap, TexCoords).r * mat.ao;

    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    
    vec3 TotalLo = vec3(0.0);

    if(dirLight.enabled)
        TotalLo += ComputePBR(normalize(-dirLight.direction), V, N, dirLight.color * dirLight.intensity, albedo, metallic, roughness, F0);

    for(int i = 0; i < numPointLight; ++i)
    {
        if(!pointLights[i].enabled)
            continue;

        vec3 L = normalize(pointLights[i].position - FragPos);
        float distance = length(pointLights[i].position - FragPos);

        float attenuation = 1.0 / (distance * distance); 

        float windowing = clamp(1.0 - pow(distance / pointLights[i].radius, 4.0), 0.0, 1.0);
        windowing *= windowing;

        vec3 radiance = pointLights[i].color * pointLights[i].intensity * attenuation;
        TotalLo += ComputePBR(L, V, N, radiance, albedo, metallic, roughness, F0);
    }

    for(int i = 0; i < numSpotLight; ++i) 
    {
        if(!spotLights[i].enabled)
            continue;

        vec3 L = normalize(spotLights[i].position - FragPos);
        float distance = length(spotLights[i].position - FragPos);

        float attenuation = 1.0 / (distance * distance);

        float theta = dot(L, normalize(-spotLights[i].direction)); 
        float epsilon = spotLights[i].cutOff - spotLights[i].outerCutOff;
        float spotIntensity = clamp((theta - spotLights[i].outerCutOff) / epsilon, 0.0, 1.0);

        vec3 radiance = spotLights[i].color * spotLights[i].intensity * attenuation * spotIntensity;
        TotalLo += ComputePBR(L, V, N, radiance, albedo, metallic, roughness, F0);
    }


    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + TotalLo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}