#version 300 es

precision mediump float;

in vec3 Position;

out vec3 TexCoords;

struct Camera {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

uniform Camera camera;
uniform mat4 skyboxModelMatrix;

void main() {
  TexCoords = Position;

  mat4 skyboxViewMatrix = mat4(mat3(camera.ViewMatrix));
  gl_Position = camera.ProjectionMatrix * skyboxViewMatrix * skyboxModelMatrix * vec4(Position, 1.0);
}
