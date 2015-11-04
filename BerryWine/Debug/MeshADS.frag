#version 430 core
smooth in vec4 FragColor;
in vec3 FragNormal;
in vec3 FragPosition;

out vec4 framebuffercolor;
layout (binding = 0) uniform
MeshMaterial {
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;
	float shininess;
}meshMat;

layout (binding = 1) uniform
LightParams {
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;
	vec4 position;
}lightparams;

void main()
{
	vec3 L = normalize(vec3(lightparams.position) - FragPosition);
   	vec3 E = normalize(-FragPosition);
   	vec3 R = normalize(-reflect(L, FragNormal));

   	vec4 Iamb = vec4(lightparams.ambient ,  1.0);

   	vec4 Idiff = vec4(lightparams.diffuse * max(dot(FragNormal,L), 0.0) , 1.0);
   	Idiff = clamp(Idiff, 0.0, 1.0);
/*
   	vec4 Ispec = vec4(lightparams.specular * pow(max(dot(R,E),0.0),0.3 * meshMat.shininess) , 1.0);
   	Ispec = clamp(Ispec, 0.0, 1.0);

	
	framebuffercolor = Iamb + Idiff + Ispec;*/

	vec4 Ispec = vec4(lightparams.specular * pow(max(dot(R,E), 0.0), 3), 1.0);

	framebuffercolor = Iamb + Idiff + Ispec;
}
