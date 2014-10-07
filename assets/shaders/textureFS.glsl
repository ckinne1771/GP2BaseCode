#version 150

out vec4 FragColor;
in vec2 vertexTexCoordsOut;

uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, vertexTexCoordsOut);
}