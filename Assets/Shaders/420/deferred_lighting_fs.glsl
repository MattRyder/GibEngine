#version 420

const int MAX_LIGHT_COUNT = 128;

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

uniform int pointLightCount;
uniform Light pointLights[MAX_LIGHT_COUNT];

in VertexShader {
    vec2 TexCoords;
    vec3 CameraPosition;
} VS;

layout(location = 0) out vec4 fragColor;

void main() {
    vec3 fragmentDiffuse = texture(framebuffer_Albedo, VS.TexCoords).rgb;
    vec3 fragmentPosition = texture(framebuffer_Position, VS.TexCoords).rgb;
    vec3 fragmentNormal = texture(framebuffer_Normal, VS.TexCoords).rgb;
    float fragmentSpecular = texture(framebuffer_Albedo, VS.TexCoords).a;

    vec3 lightColor = fragmentDiffuse * 0.25;
    vec3 viewDirection = normalize(VS.CameraPosition - fragmentPosition);

    for(int i = 0; i < pointLightCount; i++) {
	    float distanceToLight = length(pointLights[i].position - fragmentPosition);

        // This is really convenient right now. Delet later.
	    if(distanceToLight > pointLights[i].volumeRadius * pointLights[i].linearAttenuation)
		    continue;

	    vec3 lightDirection = normalize(pointLights[i].position - fragmentPosition);
	    vec3 diffuseColor = max(dot(fragmentNormal, lightDirection), 0.0) * fragmentDiffuse * pointLights[i].diffuseColor;

	    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	    float specularComponent = pow(max(dot(fragmentNormal, halfwayDirection), 0.0), 16.0);
	    vec3 specularColor = pointLights[i].specularColor * specularComponent * fragmentSpecular;
        
	    float attenuation = 1.0 / (1.0 + /*pointLights[i].linearAttenuation*/ 0.1 * distanceToLight + /*pointLights[i].quadraticAttenuation*/ 0.01 * pow(distanceToLight, 2));

	    diffuseColor *= attenuation;
	    specularColor *= attenuation;
	    lightColor += (diffuseColor + specularColor);
    }

    fragColor = vec4(lightColor, 1.0);
}