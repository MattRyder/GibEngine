#version 300 es

precision mediump float;

uniform samplerCube skyboxCubemap;

in vec3 TexCoords;
out vec4 frag_color;

void main() {
  //frag_color = vec4(TexCoords, 1.0);
  frag_color = texture(skyboxCubemap, TexCoords);
}