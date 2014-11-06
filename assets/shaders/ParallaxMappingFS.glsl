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

uniform float bias = 0.05;
uniform float scale = 0.025;

void main()
{
	float height = texture(heightMap, texCoordsOut).x;
	//bias
	height = (height * scale) - bias;
	vec2 correctedTexCoords = (height*cameraDirectionOut.xy) + texCoordsOut;

	vec3 bumpNormals = 2.0 * texture(bumpMap, correctedTexCoords).rgb - 1.0;
	bumpNormals = normalize(bumpNormals);

	float diffuseTerm = dot(bumpNormals, lightDirectionOut);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirectionOut);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseMap, texCoordsOut);
	vec4 specTextureColour = texture(specMap, texCoordsOut);

	FragColor = (ambientMaterialColour*ambientLightColour) + ((diffuseMaterialColour + diffuseTextureColour)*diffuseLightColour*diffuseTerm) + 
		((specularMaterialColour + specTextureColour)*specularLightColour*specularTerm);
}