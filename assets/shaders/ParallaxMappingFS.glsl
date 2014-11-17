#version 150

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec3 lightDirectionOut;
in vec2 texCoordsOut;



uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform sampler2D diffuseMap;
uniform sampler2D specMap;
uniform sampler2D bumpMap;
uniform sampler2D heightMap;

uniform float bias = 0.01;
uniform float scale = 0.3;

void main()
{
    //retrieve height from texture
	float height = texture(heightMap, texCoordsOut).r*scale + bias;
	height /= cameraDirectionOut.z;

    
	vec2 parallaxDirection = normalize(cameraDirectionOut.xy);
	float displacementLength = length(cameraDirectionOut);
	float parallaxLength = sqrt(displacementLength*displacementLength - cameraDirectionOut.z*cameraDirectionOut.z) / cameraDirectionOut.z;
	vec2 parallaxOffset = (parallaxDirection*parallaxLength)*scale;

    //use offset limits(scale and bias) to move texture coords
	vec2 correctedTexCoords = parallaxOffset + cameraDirectionOut.xy*height;
    
    //Calculate new texture coords, we use these instead of normal texture coords
    correctedTexCoords=texCoordsOut-correctedTexCoords;

    //get normals from normal map, rescale from 0 to 1 to -1 to 1
	vec3 bumpNormals = 2.0 * texture(bumpMap, correctedTexCoords).rgb - 1.0;
    //normalize!!
	bumpNormals = normalize(bumpNormals);

    //now use bumpnormals in reflectance calculate
	float diffuseTerm = dot(bumpNormals, lightDirectionOut);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionOut);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseMap, correctedTexCoords);
	vec4 specTextureColour = texture(specMap, correctedTexCoords);

	FragColor = (ambientMaterialColour*ambientLightColour) + ((diffuseMaterialColour + diffuseTextureColour)*diffuseLightColour*diffuseTerm) + 
		((specularMaterialColour + specTextureColour)*specularLightColour*specularTerm);
}