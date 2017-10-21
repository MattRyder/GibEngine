#version 300 es

in vec3 v_Position;
in vec2 v_TexCoords;

out vec2 TexCoords;
out vec3 CameraPosition;

struct Camera {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

uniform Camera camera;

void main() {
  TexCoords = v_TexCoords;
  CameraPosition = camera.CameraPosition;
  
  gl_Position = vec4(v_Position, 1.0);
}
