#version 300 es

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoords;
in vec3 v_Tangent;
in vec3 v_Bitangent;
in mat4 v_InstanceMatrix;

out mat4 InstanceMatrix;
out mat3 InverseTangentMatrix;
out vec4 FragmentLightSpace;
out vec3 Normal;
out vec3 FragmentPosition;
out vec3 TanViewPosition;
out vec3 TanFragPosition;
out vec2 TexCoords;

struct Camera {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

uniform mat4 u_Matrix;
uniform mat4 lightSpaceMatrix;

uniform Camera camera;

void main() {
  vec2 scaleXY = vec2(v_InstanceMatrix[0][0], v_InstanceMatrix[2][2]);
  TexCoords = v_TexCoords;
  InstanceMatrix = v_InstanceMatrix;

  mat3 normalMatrix = transpose(inverse(mat3(InstanceMatrix)));
  vec3 norm_Tangent = normalize(vec3(normalMatrix * v_Tangent));
  vec3 norm_Bitangent = normalize(vec3(normalMatrix * v_Bitangent));
  vec3 norm_Normal = normalize(vec3(normalMatrix * v_Normal));
  InverseTangentMatrix = transpose(mat3(norm_Tangent, norm_Bitangent, norm_Normal));

  FragmentPosition = vec3(InstanceMatrix * vec4(v_Position, 1.0));
  FragmentLightSpace = lightSpaceMatrix * vec4(FragmentPosition, 1.0);

  gl_Position = camera.ProjectionMatrix * camera.ViewMatrix * InstanceMatrix * vec4(v_Position, 1.0);

  TanViewPosition = InverseTangentMatrix * camera.CameraPosition;
  TanFragPosition = InverseTangentMatrix * FragmentPosition;
}
