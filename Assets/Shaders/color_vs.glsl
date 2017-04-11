#version 410

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_texCoords;

uniform mat4 modelMatrix;
uniform vec3 surfaceAmbient, surfaceDiffuse, surfaceSpecular;
out mat4 vs_ViewMatrix;
out vec3 eyePosition, eyeNormal;
out vec3 vs_surfaceAmbient, vs_surfaceDiffuse, vs_surfaceSpecular;
out vec2 texCoords;

layout (std140) uniform cameraUniformBuffer {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
};

void main() {
  texCoords = v_texCoords;
  vs_ViewMatrix = ViewMatrix;
  
  vs_surfaceAmbient = surfaceAmbient;
  vs_surfaceDiffuse = surfaceDiffuse;
  vs_surfaceSpecular = surfaceSpecular;
  
  eyePosition = vec3(ViewMatrix * modelMatrix * vec4(v_Position, 1.0));
  eyeNormal = vec3(ViewMatrix * modelMatrix * vec4(v_Position, 0.0));
  
  gl_Position = ProjectionMatrix * ViewMatrix * modelMatrix * vec4(v_Position, 1.0);
}