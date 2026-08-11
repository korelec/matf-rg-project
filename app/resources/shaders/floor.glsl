//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCords;
layout (location = 3)in vec3 aTangent;
out vec2 TexCords;
//out vec3 Normal;
out vec3 FragPos;
out mat3 TBN;

out vec3 TangentViewPos;
out vec3 TangentFragPos;
uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float tileScale;

void main() {
    vec3 Normal;
    vec3 Tangent;
    vec3 Bitangent;

    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;


    Tangent=mat3(transpose(inverse(model)))* aTangent;
    Tangent=normalize(Tangent-dot(Tangent,Normal)*Normal);
    Bitangent=cross(Normal,Tangent);
    TBN=mat3(Tangent,Bitangent,Normal);
    mat3 TBNinverse=transpose(TBN);
    TangentViewPos=TBNinverse*viewPos;
    TangentFragPos=TBNinverse*FragPos;

    TexCords = aTexCords*tileScale;
    gl_Position = projection * view * vec4(FragPos, 1.0);

}
//#shader fragment
#version 330 core

in vec2 TexCords;
//in vec3 Normal;
in mat3 TBN;
in vec3 FragPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

out vec4 FragColor;

struct Light{//fire and moon
             vec3 direction;
             vec3 position;
             vec3 color;
             float ambientStrength;
             float specStrength;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_height1;
uniform sampler2D texture_normal1;
uniform Light fire;
uniform Light moon;
uniform vec3 viewPos;

vec2 ParallaxMapping(vec2 texCords,vec3 viewDir){
    float height=texture(texture_height1,texCords).r;
    vec2 p=viewDir.xy/max(viewDir.z,0.15f)*(height*0.01f);
    return texCords-p;
}


void main() {

    vec3 viewDirTangent=normalize(TangentViewPos-TangentFragPos);
    vec2 texCords=ParallaxMapping(TexCords,viewDirTangent);

    vec3 sampledNormal = texture(texture_normal1, texCords).rgb;
    sampledNormal = normalize(sampledNormal * 2.0 - 1.0);

    vec3 texColor = texture(texture_diffuse1, texCords).rgb;


    vec3 ambient_fire = fire.ambientStrength * fire.color * texColor;
    vec3 ambient_moon=moon.ambientStrength * moon.color * texColor;

    vec3 norm     = normalize(TBN*sampledNormal);
    vec3 lightDir_fire = normalize(fire.position - FragPos);
    vec3 lightDir_moon=normalize(moon.direction);

    float diff_fire    = max(dot(norm, lightDir_fire), 0.0);
    vec3 diffuse_fire  = diff_fire * fire.color * texColor;

    float diff_moon= max(dot(norm,lightDir_moon),0.0);
    vec3 diffuse_moon=diff_moon*moon.color* texColor;


    vec3 viewDir  = normalize(viewPos - FragPos);
    vec3 reflectDir_fire = reflect(-lightDir_fire, norm);
    float spec_fire    = pow(max(dot(viewDir, reflectDir_fire), 0.0), 16.0);
    vec3 specular_fire = fire.specStrength * spec_fire * fire.color;

    vec3 reflectDir_moon=reflect(-lightDir_moon,norm);
    float spec_moon=pow(max(dot(viewDir,reflectDir_moon),0.0),4.0);
    vec3 specular_moon=moon.specStrength * spec_moon * moon.color;

    float dist        = length(fire.position- FragPos);
    float attenuation = 1.0 / (1.0 + 0.02 * dist + 0.005 * dist * dist)*fire.ambientStrength;//only for fire

    vec3 result_fire = (ambient_fire + (diffuse_fire + specular_fire) * attenuation);
    vec3 result_moon=ambient_moon + diffuse_moon + specular_moon;
    vec3 result=result_fire+result_moon;

    FragColor = vec4(result, 1.0);//
}
