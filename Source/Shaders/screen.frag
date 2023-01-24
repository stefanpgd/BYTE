#version 460 core
out vec4 FragColor;
  
in vec2 uv;

uniform sampler2D sceneTexture;
uniform sampler2D bloomTexture;

uniform float exposure;

void main()
{ 
    const float gamma = 2.2;
    vec3 hdrColor = texture(sceneTexture, uv).rgb;      
    vec3 bloomColor = texture(bloomTexture, uv).rgb;
    hdrColor += bloomColor;

    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure); // Exposure Tonemapping
    mapped = pow(mapped, vec3(1.0 / gamma));             // Gamma Correction
  
    FragColor = vec4(mapped, 1.0);
}