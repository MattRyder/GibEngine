#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 2) in vec2 v_TexCoords;

out VertexShader {
  vec2 TexCoords;
  vec3 CameraPosition;
} VS;

layout (std140) uniform cameraUBO {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

void main() {
  VS.TexCoords = v_TexCoords;
  
  gl_Position = vec4(v_Position, 1.0);
}
