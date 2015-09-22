#version 430 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in mat4 viewMat;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec4 FragColor;
void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0f);
	FragColor = vec4(Color, 1.0f);
}
