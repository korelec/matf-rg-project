//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCords;

out vec2 TexCords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCords = aTexCords;
    gl_Position = projection * view * vec4(FragPos, 1.0);

}
//#shader fragment
#version 330 core

in vec2 TexCords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Light{//fire and moon
    vec3 direction;
    vec3 position;
    vec3 color;
    float ambientStrength;
    float specStrength;
};

uniform sampler2D texture_diffuse1;
uniform Light fire;
uniform vec3 viewPos;

void main() {
    vec3 texColor = texture(texture_diffuse1, TexCords).rgb;


    vec3 ambient = fire.ambientStrength * fire.color * texColor;

    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(fire.position - FragPos);
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = diff * fire.color * texColor;

    vec3 viewDir  = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec    = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    vec3 specular = fire.specStrength * spec * fire.color;

    float dist        = length(fire.position- FragPos);
    float attenuation = 1.0 / (1.0 + 0.02 * dist + 0.005 * dist * dist);

    vec3 result = (ambient + (diffuse + specular) * attenuation);

     FragColor = vec4(result, 1.0);//
}
