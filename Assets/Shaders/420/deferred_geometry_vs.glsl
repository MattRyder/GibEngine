#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoords;
layout(location = 3) in vec3 v_Tangent;
layout(location = 4) in vec3 v_Bitangent;
layout(location = 5) in mat4 v_InstanceMatrix;

uniform mat4 u_Matrix;
uniform mat4 lightSpaceMatrix;

out VertexShader {
  mat4 InstanceMatrix;
  mat3 InverseTangentMatrix;
  vec4 FragmentLightSpace;
  vec3 Normal;
  vec3 FragmentPosition;
  vec3 TanViewPosition;
  vec3 TanFragPosition;
  vec2 TexCoords;
} VS;

layout (std140) uniform cameraUBO {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

void main() {
  VS.TexCoords = v_TexCoords;
  VS.InstanceMatrix = v_InstanceMatrix;

  mat3 normalMatrix = transpose(inverse(mat3(VS.InstanceMatrix)));
  vec3 norm_Tangent = normalize(vec3(normalMatrix * v_Tangent));
  vec3 norm_Bitangent = normalize(vec3(normalMatrix * v_Bitangent));
  vec3 norm_Normal = normalize(vec3(normalMatrix * v_Normal));
  VS.InverseTangentMatrix = transpose(mat3(norm_Tangent, norm_Bitangent, norm_Normal));

  VS.FragmentPosition = vec3(VS.InstanceMatrix * vec4(v_Position, 1.0));
  VS.FragmentLightSpace = lightSpaceMatrix * vec4(VS.FragmentPosition, 1.0);

  gl_Position = ProjectionMatrix * ViewMatrix * VS.InstanceMatrix * vec4(v_Position, 1.0);

  VS.TanViewPosition = VS.InverseTangentMatrix * CameraPosition;
  VS.TanFragPosition = VS.InverseTangentMatrix * VS.FragmentPosition;
}
