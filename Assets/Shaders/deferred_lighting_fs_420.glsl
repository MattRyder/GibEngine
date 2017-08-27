#version 420

struct Light {
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float linearAttenuation;
  float quadraticAttenuation;
  float volumeRadius;
};

layout(binding = 0) uniform sampler2D framebuffer_Position;
layout(binding = 1) uniform sampler2D framebuffer_Albedo;
layout(binding = 2) uniform sampler2D framebuffer_Normal;

const int LIGHT_COUNT = (10 * 10) + 1;
uniform Light pointLights[LIGHT_COUNT];

in VertexShader {
  vec2 TexCoords;
  vec3 CameraPosition;
} VS;

out vec4 fragColor;

void main() {
  vec3 fragmentDiffuse = texture(framebuffer_Albedo, VS.TexCoords).rgb;
	vec3 fragmentPosition = texture(framebuffer_Position, VS.TexCoords).rgb;
	vec3 fragmentNormal = texture(framebuffer_Normal, VS.TexCoords).rgb;
	float fragmentSpecular = texture(framebuffer_Albedo, VS.TexCoords).a;

	vec3 lightColor = fragmentDiffuse * 0.5;
	vec3 viewDirection = normalize(VS.CameraPosition - fragmentPosition);

	for(int i = 0; i < LIGHT_COUNT; i++) {
		float distanceToLight = length(pointLights[i].position - fragmentPosition);

		if(distanceToLight > pointLights[i].volumeRadius)
				continue;

		vec3 lightDirection = normalize(pointLights[i].position - fragmentPosition);
		vec3 diffuseColor = max(dot(fragmentNormal, lightDirection), 0.0) * fragmentDiffuse * pointLights[i].diffuseColor;

		vec3 halfwayDirection = normalize(lightDirection + viewDirection);
		float specularComponent = pow(max(dot(fragmentNormal, halfwayDirection), 0.0), 2.0);
		vec3 specularColor = pointLights[i].specularColor * specularComponent * fragmentSpecular;
        
		float attenuation = 1.0 / (1.0 + pointLights[i].linearAttenuation * distanceToLight + pointLights[i].quadraticAttenuation * pow(distanceToLight, 2));

		diffuseColor *= attenuation;
		specularColor *= attenuation;
		lightColor += (diffuseColor + specularColor);
	}

	fragColor = vec4(lightColor, 1.0);
}