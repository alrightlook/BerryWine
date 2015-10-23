#version 430 core
smooth in vec4 FragColor;
out vec4 framebuffercolor;
layout (binding = 0) uniform
MeshMaterial {
	vec3 ambient;
	vec3 specular;
	vec3 diffuse;
}meshMat;

void main()
{

	if (meshMat.diffuse.x != 0.0)
	{
		framebuffercolor = vec4 (1.0, 0.0, 0.0, 1.0);
	}
	else 
	{
		framebuffercolor = FragColor;	
	}
	
	framebuffercolor = vec4(meshMat.specular * 0.2, 1.0);
}
