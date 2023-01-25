#version 460 core
out vec4 FragColor;
  
in vec2 uv;

uniform sampler2D sceneTexture;
uniform sampler2D bloomTexture;

uniform float exposure;
uniform vec2 rOffset;
uniform vec2 gOffset;
uniform vec2 bOffset;

void main()
{ 
    const float gamma = 2.2;
    vec3 color;
    color.r = texture(sceneTexture, uv + rOffset).r;
    color.g = texture(sceneTexture, uv + gOffset).g;
    color.b = texture(sceneTexture, uv + bOffset).b;

    vec3 bloomColor = texture(bloomTexture, uv).rgb;
    color += bloomColor;

    vec3 mapped = vec3(1.0) - exp(-color * exposure);    // Exposure Tonemapping
    mapped = pow(mapped, vec3(1.0 / gamma));             // Gamma Correction
  
    FragColor = vec4(mapped, 1.0);
}