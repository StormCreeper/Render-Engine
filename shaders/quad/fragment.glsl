#version 460 core
out vec4 FragColor;
  
in vec2 textureCoords;

uniform sampler2D screenTexture;

void main() {
    FragColor = vec4(texture(screenTexture, textureCoords).xyz, 1);
} 