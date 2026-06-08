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
    Normal = aNormal;
    TexCords = aTexCords;
    gl_Position = projection * view * vec4(FragPos, 1.0);

}
//#shader fragment
#version 330 core

in vec2 TexCords;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

void main() {
        FragColor = vec4(1.0f, 1.0f-(1.0/(FragPos.y)), 0.0f, 1.0);
}


