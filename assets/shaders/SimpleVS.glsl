/*----------------- "exampleVertexShader.vert" -----------------*/
 
#version 400
 

in  vec3 vertexPosition;
in vec4 vertexColour;
out vec4 vertexColourOut;
 
void main() 
{
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
	vertexColourOut = vertexColour;
}
/*--------------------------------------------------------------*/