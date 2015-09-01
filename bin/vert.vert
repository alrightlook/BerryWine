#version 440
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

uniform mat4 Projection;
uniform mat4 ModelView;

out vec4 FragColor;
void main()
{
	gl_Position = Projection * ModelView * vec4(Position, 1.0f);
	FragColor = vec4(Color, 1.0f);
}