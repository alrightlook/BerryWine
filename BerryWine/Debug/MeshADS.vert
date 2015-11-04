#version 430 core
layout (location = 0) in vec3 PositionMesh;
layout (location = 1) in vec3 Color;
layout (location = 2) in mat4 viewMat;
layout (location = 3) in vec3 VertexNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec4 FragColor;
out vec3 FragNormal;
out vec3 FragPosition;

void main()
{

	gl_Position = projectionMatrix * viewMatrix * vec4(PositionMesh, 1.0f);
	FragNormal = VertexNormal;
	FragPosition = PositionMesh;

	FragColor = vec4(1.0, 0.0, 1.0, 0.0);
}
