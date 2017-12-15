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

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_depth0;

out vec4 frag_color[4];

void main () 
{
  vec3 diffuseColor = texture(texture_diffuse0, TexCoords).rgb;
  vec3 normalColor = texture(texture_normal0, TexCoords).rgb;
  vec3 specularColor = texture(texture_specular0, TexCoords).rgb;
	
	// gamma
  float gamma = 1.0;
	vec3 frag_rgb = (diffuseColor + normalColor + specularColor);
	frag_rgb = pow(frag_rgb, vec3(1.0/gamma));
	frag_color[3] = vec4(frag_rgb, 1.0);
}