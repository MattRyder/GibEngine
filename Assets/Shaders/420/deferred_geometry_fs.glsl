#version 420

layout (std140) uniform materialUBO {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

in VertexShader {
  mat4 InstanceMatrix;
  mat3 InverseTangentMatrix;
  vec4 FragmentLightSpace;
  vec3 Normal;
  vec3 FragmentPosition;
  vec3 TanViewPosition;
  vec3 TanFragPosition;
  vec2 TexCoords;
} VS;

layout(location = 0) out vec4 g_Position;
layout(location = 1) out vec4 g_Albedo;
layout(location = 2) out vec3 g_Normal;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_depth0;

const float Z_NEAR = 1.0;
const float Z_FAR = 250.0;

float linearDepth(float depthValue) {
  // translate to normalized device coordinate space:
  float z = depthValue * 2.0 - 1.0;
  return (2.0 * Z_NEAR * Z_FAR) / (Z_FAR + Z_NEAR - z * (Z_FAR + Z_NEAR));
}

void main() {
  g_Position = vec4(VS.FragmentPosition, 1.0);
  g_Position.a = gl_FragCoord.z; //linearDepth(gl_FragCoord.z),
  g_Normal = normalize(texture(texture_normal0, VS.TexCoords).rgb);
  g_Albedo.rgb = texture(texture_diffuse0, VS.TexCoords).rgb;
  g_Albedo.a = texture(texture_specular0, VS.TexCoords).r;
}
