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

// Must match engine convention: Mesh binds diffuse samplers as texture_diffuse1, texture_diffuse2, ...
uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    vec3 texColor = texture(texture_diffuse1, TexCords).rgb;

    // Ambient — malo topline čak i u senci
    float ambientStrength = 0.75;
    vec3 ambient = ambientStrength * lightColor * texColor;

    // Diffuse
    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = diff * lightColor * texColor;

    float specStrength = 0.05;
    vec3 viewDir  = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec    = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    vec3 specular = specStrength * spec * lightColor;

    float dist        = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.14 * dist + 0.07 * dist * dist);

    vec3 result = (ambient + (diffuse + specular) * attenuation);

     FragColor = vec4(result, 1.0);
}
