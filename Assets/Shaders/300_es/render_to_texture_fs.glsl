#version 300 es

precision mediump float;

in vec2 TexCoords;

out vec4 color;

uniform sampler2D renderedTexture;

void main() {
  color = vec4(texture(renderedTexture, TexCoords).rgb, 1.0);
}