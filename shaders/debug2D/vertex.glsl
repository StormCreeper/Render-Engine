#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec3 vertexNormal;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexNormal = aNormal;
    vertexColor = vec3(1.0, 1.0, 1.);
}