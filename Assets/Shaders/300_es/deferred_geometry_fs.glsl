#version 300 es

precision mediump float;

in mat4 InstanceMatrix;
in mat3 InverseTangentMatrix;
in vec4 FragmentLightSpace;
in vec3 Normal;
in vec3 FragmentPosition;
in vec3 TanViewPosition;
in vec3 TanFragPosition;
in vec2 TexCoords;

out vec4 g_Position;
out vec4 g_Albedo;
out vec3 g_Normal;

out vec4 fragColor[3];

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_depth0;

const float Z_NEAR = 1.0;
const float Z_FAR = 2000.0;

float linearDepth(float depthValue) {
  // translate to normalized device coordinate space:
  float z = depthValue * 2.0 - 1.0;
  return (2.0 * Z_NEAR * Z_FAR) / (Z_FAR + Z_NEAR - z * (Z_FAR + Z_NEAR));
}

void main() {
  fragColor[0] = vec4(FragmentPosition, 1.0);  
  fragColor[0].a = linearDepth(gl_FragCoord.z);
  fragColor[1] = vec4(normalize(texture(texture_normal0, TexCoords).rgb), 0.0);
  fragColor[2].rgb = texture(texture_diffuse0, TexCoords).rgb;
  fragColor[2].a = texture(texture_specular0, TexCoords).r;
}
