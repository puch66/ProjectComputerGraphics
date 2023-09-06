#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 DlightDir;		// direction of the direct light
	vec3 DlightColor;	// color of the direct light
	vec3 AmbLightColor;	// ambient light
	vec3 eyePos;		// position of the viewer
    vec3 lightPos;
} gubo;

layout(set = 1, binding = 0) uniform UniformBufferObject {
	float amb;
	float gamma;
	vec3 sColor;
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

const float beta = 2.0f;
const float g = 1.5;
const float cosout = 0.85;
const float cosin  = 0.95;

layout(set = 1, binding = 1) uniform sampler2D tex;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {
    
    vec3 Norm = N;
    vec3 EyeDir = V;
    vec3 lx = normalize(gubo.lightPos - fragPos);
    vec3 lightDir = L;
    float cosAlpha = dot(lx, lightDir);
    vec3 lightColor = pow((g/length(gubo.lightPos - fragPos)), beta) * gubo.DlightColor.rgb * clamp((cosAlpha - cosout)/(cosin - cosout), 0.0, 1.0);
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//vec3 Ms - specular color of the surface
	//float gamma - Exponent for power specular term

    vec3 Diffuse = texture(tex, fragUV).rgb * 0.995f * clamp(dot(Norm, lightDir),0.0,1.0);
    vec3 Specular = vec3(pow(clamp(dot(Norm, normalize(lightDir + EyeDir)),0.0,1.0), 160.0f));
	
	return Diffuse + Specular;
}

void main() {
    vec3 EyeDir = normalize(gubo.eyePos - fragPos);
    vec3 Norm = normalize(fragNorm);
	
	vec3 lightDir = gubo.DlightDir;
	vec3 lightColor = gubo.DlightColor.rgb;

	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, vec3(1.0f), 160.0f);
	vec3 Ambient = texture(tex, fragUV).rgb * 0.005f;
	
    outColor = vec4(clamp((DiffSpec) * lightColor + Ambient,0.0,1.0), 1.0f);
}
