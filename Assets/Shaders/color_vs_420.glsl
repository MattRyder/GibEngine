#version 420

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoords;
layout(location = 3) in vec3 v_Tangent;
layout(location = 4) in vec3 v_Bitangent;
layout(location = 5) in mat4 v_InstanceMatrix;
//layout(location = 5) in int bone_id;

uniform mat4 u_Matrix;
uniform mat4 lightSpaceMatrix;

out mat4 vs_InstanceMatrix;
out mat3 vs_InverseTangentMatrix;
out vec4 vs_FragmentLightSpace;
out vec3 vs_Normal, vs_FragmentPosition, vs_TanViewPosition, vs_TanFragPosition;
out vec2 vs_TexCoords;

layout (std140) uniform cameraUBO {
  mat4 ProjectionMatrix;
  mat4 ViewMatrix;
  vec3 CameraPosition;
};

void main() {
  vs_TexCoords = v_TexCoords;
  vs_InstanceMatrix = v_InstanceMatrix;

  mat3 normalMatrix = transpose(inverse(mat3(vs_InstanceMatrix)));
  vec3 norm_Tangent = normalize(vec3(normalMatrix * v_Tangent));
  vec3 norm_Bitangent = normalize(vec3(normalMatrix * v_Bitangent));
  vec3 norm_Normal = normalize(vec3(normalMatrix * v_Normal));
  vs_InverseTangentMatrix = transpose(mat3(norm_Tangent, norm_Bitangent, norm_Normal));

  vs_FragmentPosition = vec3(vs_InstanceMatrix * vec4(v_Position, 1.0));
  vs_FragmentLightSpace = lightSpaceMatrix * vec4(vs_FragmentPosition, 1.0);

  gl_Position = ProjectionMatrix * ViewMatrix * vs_InstanceMatrix * vec4(v_Position, 1.0);

  vs_TanViewPosition = vs_InverseTangentMatrix * CameraPosition;
  vs_TanFragPosition = vs_InverseTangentMatrix * vs_FragmentPosition;
}
