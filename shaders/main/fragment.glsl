#version 330 core
out vec4 FragColor;
  
in vec3 vertexColor;
in vec3 vertexNormal;

void main() {
    vec3 objColor = vertexColor;
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objColor;

    vec3 lightColor = vec3(1.0, 1.0, 0.9);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    float diff = max(dot(vertexNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * 0.9;

    vec3 result = (ambient + diffuse) * objColor;

    FragColor = vec4(result, 1.0);
} 