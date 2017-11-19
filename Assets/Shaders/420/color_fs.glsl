#version 420

// struct Light {
// 	vec3 position;
// 	vec3 ambientColor;
// 	vec3 diffuseColor;
// 	vec3 specularColor;
// 	float attenuation;
// };

// struct DirectionalLight {
// 	vec3 position;
// 	vec3 direction;
// 	vec3 ambientColor;
// 	vec3 diffuseColor;
// 	vec3 specularColor;
// };

// uniform Light pointLights[1];
// uniform DirectionalLight directionalLights[1];

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

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_depth0;

// layout(binding = 5) uniform sampler2D texture_depthMap;

// uniform float heightScale;
// uniform vec3 surfaceAmbient, surfaceDiffuse, surfaceSpecular;

// in vec4 vs_FragmentLightSpace;
// in mat3 vs_InverseTangentMatrix;
// in vec3 vs_Normal, vs_FragmentPosition;
// in vec2 vs_TexCoords;

// in vec3 vs_TanViewPosition, vs_TanFragPosition;

out vec4 frag_color;

void main() {	
    
    vec3 diffuseColor = texture(texture_diffuse0, VS.TexCoords).rgb;
    vec3 normalColor = texture(texture_normal0, VS.TexCoords).rgb;
    vec3 specularColor = texture(texture_specular0, VS.TexCoords).rgb;
	
	// gammaw
	 float gamma = 1.0;
	 vec3 frag_rgb = (diffuseColor + normalColor + specularColor);
	 frag_rgb = pow(frag_rgb, vec3(1.0/gamma));
	 frag_color = vec4(frag_rgb, 1.0);
}