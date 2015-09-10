#version 440 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec4 FragColor;
void main()
{
	//gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0f);
	//gl_Position = /* wprojectionMatrix * viewMatrix * modelMatrix * */vec4(Position, 1.0f);

	gl_Position = projectionMatrix * viewMatrix * vec4(Position, 1.0f) ;

	FragColor = vec4(Color, 1.0f);
}