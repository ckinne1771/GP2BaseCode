/*----------------- "exampleVertexShader.vert" -----------------*/
 
#version 400
 

in  vec3 vertexPosition;
in vec4 vertexColourIn;
out vec4 vertexColour;

uniform mat4 MVP;
 
void main() 
{
	vertexColour = vertexColourIn;
	gl_Position = MVP*vec4(vertexPosition, 1.0);
}
/*--------------------------------------------------------------*/