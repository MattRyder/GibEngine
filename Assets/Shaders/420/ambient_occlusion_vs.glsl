#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 2) in vec2 v_TexCoords;

layout (std140) uniform cameraUBO {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
};

out VertexShader {
  mat4 ViewMatrix;
  mat4 ProjectionMatrix;
  vec2 TexCoords;
} VS;

void main() {
  VS.ViewMatrix = ViewMatrix;
  VS.ProjectionMatrix = ProjectionMatrix;
  VS.TexCoords = v_TexCoords;

  gl_Position = vec4(v_Position, 1.0);
}
