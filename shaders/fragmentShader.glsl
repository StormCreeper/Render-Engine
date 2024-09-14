#version 330 core
out vec4 FragColor;
  
in vec3 vertexColor;
in vec3 vertexNormal;

void main() {
    FragColor = vec4(vertexColor * vertexNormal, 1.0);
} 