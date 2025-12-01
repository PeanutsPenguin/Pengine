#version 330 core

const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 10;

struct DirectionalLight
{
    vec3 Color;
    vec3 Direction;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct PointLight
{
    vec3 Color;
    vec3 WorldPos; 
    float AmbientIntensity;
    float DiffuseIntensity;
//    vec3 LocalPos; 
    float Constant;
    float Linear;
    float Exp;
};

struct SpotLight
{
    vec3 Color;
    vec3 Direction;
    vec3 WorldPos; 
    float AmbientIntensity;
    float DiffuseIntensity;
    float Constant;
    float Linear;
    float Exp;
    float Cutoff;
};

struct Material
{
    //Might change those to smaplers
    vec3 AmbientColor;
    vec3 DiffuseColor;
    vec3 SpecularColor;
};

struct PBRLight {
    vec4 PosDir;   // if w == 1 position, else direction
    vec3 Intensity;
};

struct PBRMaterial
{
    float Roughness;
    bool IsMetal;
    vec3 Color;
};

//DirLight
uniform DirectionalLight gDirectionalLight;

//PointLight
uniform int gNumPointLights;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];

//SpotLight
uniform int gNumSpotLights;
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];

//Material
uniform Material gMaterial;

//Camera Position
uniform vec3 gviewPos;

//Is Model PBR
uniform bool gIsPBR = true;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

vec3 getPBRDirectionnalLight(vec3 Normal)
{
    return CalcPBRLighting(gDirectionalLight.Base, gDirectionalLight.Direction, true, Normal);
}



vec4 getPBRLight()
{
    vec3 Normal = normalize(Normal);

    vec3 TotalLight = getPBRDirectionnalLight(Normal);

    for (int i = 0 ;i < gNumPointLights ;i++) {
        TotalLight += CalcPBRPointLight(gPointLights[i], Normal);
    }

    // HDR tone mapping
    TotalLight = TotalLight / (TotalLight + vec3(1.0));

    // Gamma correction
    vec4 FinalLight = vec4(pow(TotalLight, vec3(1.0/2.2)), 1.0);

    return FinalLight;
}


void main()
{
    if (gIsPBR) 
    {
        FragColor = getPBRLight();
    } 
//    else 
//    {
//        FragColor = CalcPhongLighting();
//    }
}





