#version 430 core
smooth in vec4 FragColor;
out vec4 framebuffercolor;
void main()
{
	framebuffercolor = FragColor;
}