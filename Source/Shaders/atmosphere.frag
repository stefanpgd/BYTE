#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color1;
uniform vec3 color2;

uniform float bloomIntensity;
uniform float atmosphereDensity;
uniform float time;
uniform vec3 starColor;
uniform float cutoff;
uniform float maxBright;

uniform vec3 cameraPosition;
uniform float radius;
uniform vec3 sphereOrigin;

uniform sampler2D texture_albedo;

vec2 raySphereIntersection(vec3 ro, vec3 rd, vec3 so, float sr)
{
	float t = dot(so - ro, rd);
	vec3 P = ro + rd * t;
	float y = length(so - P);

	if(y <= sr)
	{
		float x = sqrt(sr * sr - y * y);
		float t1 = t - x;
		float t2 = t + x;

		return vec2(t1, t2);
	}

	return vec2(-1);
}

vec3 raySphereNormal(vec3 ro, vec3 rd, vec3 so, float sr)
{
	float t = dot(so - ro, rd);
	vec3 P = ro + rd * t;
	float y = length(so - P);

	float x = sqrt(sr * sr - y * y);
	float t1 = max(t - x, 0.0);
	float t2 = t + x;
	vec3 np = ro + rd*max(min(t,t2), 0.0);
	vec3 normal = normalize(np - so);

	return normal;
}

void main()
{
	vec3 rayDir = normalize(FragPos - cameraPosition);

	vec2 distanceTravelled = raySphereIntersection(cameraPosition, rayDir, sphereOrigin, radius);
	if(distanceTravelled == vec2(-1))
	{
		discard;
	}

	float weight = clamp(length((distanceTravelled.y - distanceTravelled.x)) * atmosphereDensity, 0.0, 1.0);

	vec3 norm = raySphereNormal(cameraPosition, rayDir, sphereOrigin, radius);
	float diff = smoothstep(cutoff, maxBright, (dot(norm, normalize(-FragPos)) + 1.0) * 0.5);
	vec3 c = mix(color1, color2, diff);
	weight = weight * diff;

	FragColor = vec4(c, weight);
	BrightColor = FragColor * bloomIntensity;
}