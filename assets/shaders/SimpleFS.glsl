/*---------------- "exampleFragmentShader.frag" ----------------*/
 
#version 400
 
out vec4 FragColor;
in vec4 vertexColour;

void main() 
{
	FragColor = vertexColour;
}
/*--------------------------------------------------------------*/