#version 450

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

uniform Material material;

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posLightDirVec = normalize(lightPos0 - vs_position);
	vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	float diffuse = clamp(dot(posLightDirVec, vs_normal), 0, 1);
	return material.diffuse * diffuse;
}
vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewVec = normalize(cameraPos - vs_position);
	float specConst = pow(max(dot(posToViewVec, reflectDirVec), 0), 30);
	return material.specular * specConst;
}

void main()
{
	vec3 ambientFinal = calculateAmbient(material);
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);
	vec3 specFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0);

	fs_color = texture(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.f) + (vec4(diffuseFinal, 1.f) + vec4(specFinal, 1.f)));
}