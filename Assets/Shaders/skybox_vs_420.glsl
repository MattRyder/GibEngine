#version 410

layout(location = 0) in vec3 v_Position;

uniform mat4 skyboxModelMatrix;

out vec3 vs_TexCoords;

layout (std140) uniform cameraUBO {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
};


void main() {
  vs_TexCoords = v_Position;

  mat4 skyboxViewMatrix = mat4(mat3(ViewMatrix));
  gl_Position = ProjectionMatrix * skyboxViewMatrix * skyboxModelMatrix * vec4(v_Position, 1.0);
}
