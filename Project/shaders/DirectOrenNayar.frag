#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 lightPos;
	vec3 DlightDir;		// direction of the direct light
	vec3 DlightColor;	// color of the direct light
	vec3 AmbLightColor;	// ambient light
	vec3 eyePos;		// position of the viewer
} gubo;

layout(set = 1, binding = 0) uniform UniformBufferObject {
	float amb;
	float gamma;
	vec3 sColor;
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(set = 1, binding = 1) uniform sampler2D tex;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, float sigma) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//float sigma - Roughness of the model

	float theta_i = acos(dot(L, N));
	float theta_r = acos(dot(V, N));
	float alpha = max(theta_i, theta_r);
	float beta = min(theta_i, theta_r);

	float A = 1.0f - 0.5f * pow(sigma, 2.0) / (pow(sigma, 2.0) + 0.33f);
	float B = 0.45f * pow(sigma, 2.0) / (pow(sigma, 2.0) + 0.09f);

	vec3 vi = normalize(L - dot(L, N) * N);
	vec3 vr = normalize(L - dot(V, N) * N);
	float G = max(0, dot(vi, vr));

	vec3 _L =  Md * clamp(dot(L, N), 0.0, 1.0);

	vec3 Diffuse = _L * (A + B * G * sin(alpha) * tan(beta)); 
	return Diffuse;
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	
	//spot light model
	vec3 lightDir = gubo.DlightDir;
	vec3 lightColor = gubo.DlightColor.rgb;

	//oren nayar brdf
	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, 1.1f);
	vec3 Ambient = texture(tex, fragUV).rgb * 0.05f;
	
	outColor = vec4(clamp(0.95 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}
