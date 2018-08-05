#version 420

layout(binding = 0) uniform sampler2D texture_Position;
layout(binding = 1) uniform sampler2D texture_Normal;
layout(binding = 2) uniform sampler2D texture_Noise;

const int KERNEL_SIZE = 64;
uniform vec3 ssao_Kernel[KERNEL_SIZE];

const vec2 noiseScale = vec2(1920.0 / 4.0, 1080.0 / 4.0);

in VertexShader {
  mat4 ViewMatrix;
  mat4 ProjectionMatrix;
  vec2 TexCoords;
} VS;

out float fragColor;

void main() {
  vec3 ssaoPos = texture(texture_Position, VS.TexCoords).xyz;
  vec3 ssaoNormal = normalize(texture(texture_Normal, VS.TexCoords).rgb);
  vec3 ssaoNoise = normalize(texture(texture_Noise, VS.TexCoords * noiseScale).xyz);

  vec3 tangent = normalize(ssaoNoise - ssaoNormal * dot(ssaoNoise, ssaoNormal));
  vec3 bitangent = cross(ssaoNormal, tangent);
  mat3 tbnMatrix = mat3(tangent, bitangent, ssaoNormal);

  float occlusionRadius = 0.33;
  float occlusion = 0.0;
  for(int i = 0; i < KERNEL_SIZE; i++) {
    vec3 ssaoSample = tbnMatrix * ssao_Kernel[i];
    ssaoSample = ssaoPos + ssaoSample * occlusionRadius;

    vec4 offset = vec4(ssaoSample, 1.0);
    offset = VS.ProjectionMatrix * VS.ViewMatrix * offset;
    offset.xyz /= offset.w; // perspective divide
    offset.xyz = offset.xyz * 0.5 + 0.5;

    // read depth from position sampler
    float sampleDepth = texture(texture_Position, offset.xy).z;
    float rangeCheck = smoothstep(0.0, 1.0, length(ssaoPos.z - sampleDepth) / occlusionRadius);
    occlusion += (sampleDepth >= ssaoSample.z + 0.025 ? 1.0 : 0.0) * rangeCheck;
  }


  occlusion = 1.0 - (occlusion / KERNEL_SIZE);
  fragColor = occlusion;
}
