#version 420

in vec2 TexCoords;

layout(location = 0) out vec4 color;

uniform sampler2D renderedTexture;

void main() {
  color = vec4(texture(renderedTexture, TexCoords).rgb, 1.0);
}