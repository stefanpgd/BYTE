#version 460 core
out vec4 FragColor;
  
in vec2 uv;

uniform sampler2D sceneTexture;
uniform sampler2D bloomTexture;

uniform float exposure;
uniform vec2 rOffset;
uniform vec2 gOffset;
uniform vec2 bOffset;

uniform bool centeredCA;
uniform float centeredCAStrength;

void main()
{ 
    const float gamma = 2.2;
    vec3 color;

    if(centeredCA)
    {
        vec2 center = vec2(0.5, 0.5);
        vec2 dir = uv - center;
        float strength = (length(dir) * 2.0) * centeredCAStrength; // max length = 0.5, thus * 2;

        color.r = texture(sceneTexture, uv + (rOffset * strength)).r;
        color.g = texture(sceneTexture, uv + (gOffset * strength)).g;
        color.b = texture(sceneTexture, uv + (bOffset * strength)).b;
    }
    else
    {
        color.r = texture(sceneTexture, uv + rOffset).r;
        color.g = texture(sceneTexture, uv + gOffset).g;
        color.b = texture(sceneTexture, uv + bOffset).b;
    }

    vec3 bloomColor = texture(bloomTexture, uv).rgb;
    color += bloomColor;

    vec3 mapped = vec3(1.0) - exp(-color * exposure);    // Exposure Tonemapping
    mapped = pow(mapped, vec3(1.0 / gamma));             // Gamma Correction
  
    FragColor = vec4(mapped, 1.0);
}