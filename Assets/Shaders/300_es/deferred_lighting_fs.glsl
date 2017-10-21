#version 300 es

precision mediump float;

in vec2 TexCoords;
in vec3 CameraPosition;

out vec4 fragColor;

struct Light {
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float linearAttenuation;
  float quadraticAttenuation;
  float volumeRadius;
};

uniform sampler2D framebuffer_Position;
uniform sampler2D framebuffer_Albedo;
uniform sampler2D framebuffer_Normal;

const int LIGHT_COUNT = 2 * 2;
uniform Light pointLights[LIGHT_COUNT];

void main() {
  	vec3 fragmentDiffuse = texture(framebuffer_Albedo, TexCoords).rgb;
	vec3 fragmentPosition = texture(framebuffer_Position, TexCoords).rgb;
	vec3 fragmentNormal = texture(framebuffer_Normal, TexCoords).rgb;
	float fragmentSpecular = texture(framebuffer_Albedo, TexCoords).a;

	vec3 lightColor = fragmentDiffuse * 0.5;
	vec3 viewDirection = normalize(CameraPosition - fragmentPosition);

	for(int i = 0; i < LIGHT_COUNT; i++) {
	    float distanceToLight = length(pointLights[i].position - fragmentPosition);

		if(distanceToLight > pointLights[i].volumeRadius * 10.0)
		 	continue;

		vec3 lightDirection = normalize(pointLights[i].position - fragmentPosition);
		vec3 diffuseColor = max(dot(fragmentNormal, lightDirection), 0.0) * fragmentDiffuse * pointLights[i].diffuseColor;

		vec3 halfwayDirection = normalize(lightDirection + viewDirection);
		float specularComponent = pow(max(dot(fragmentNormal, halfwayDirection), 0.0), 2.0);
		vec3 specularColor = pointLights[i].specularColor * specularComponent * fragmentSpecular;
        
		float attenuation = 1.0 / (1.0 + pointLights[i].linearAttenuation * distanceToLight + pointLights[i].quadraticAttenuation * pow(distanceToLight, 2.0));

		diffuseColor *= attenuation;
		specularColor *= attenuation;
		lightColor += (diffuseColor + specularColor);
	}

	fragColor = vec4(lightColor, 1.0);
}