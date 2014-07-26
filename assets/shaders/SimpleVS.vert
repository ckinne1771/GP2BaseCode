/*----------------- "exampleVertexShader.vert" -----------------*/
 
#version 400
 

in  vec3 vertexPosition;
 
void main() 
{
    gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
}
/*--------------------------------------------------------------*/