#version 420

uniform samplerCube skyboxCubemap;

in vec3 vs_TexCoords;
out vec4 frag_color;

void main() {
  frag_color = texture(skyboxCubemap, vs_TexCoords);
}
