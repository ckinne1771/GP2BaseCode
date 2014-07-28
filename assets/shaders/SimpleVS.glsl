/*----------------- "exampleVertexShader.vert" -----------------*/
 
#version 400
 

in  vec3 vertexPosition;
in vec4 vertexColourIn;
out vec4 vertexColour;
 
void main() 
{
	vertexColour = vertexColourIn;
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
}
/*--------------------------------------------------------------*/