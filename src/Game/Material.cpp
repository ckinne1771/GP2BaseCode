#include "Game\Material.h"
#include "Shader.h"

Material::Material()
{
	m_ShaderProgram = -1;
	m_Type = "Material";
}

Material::~Material()
{

}

void Material::createShaderProgram()
{
	m_ShaderProgram=glCreateProgram();
}

bool Material::linkShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);

	if (checkForLinkErrors(m_ShaderProgram))
		return false;

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//We can just in this in the shader! - https://www.opengl.org/wiki/Layout_Qualifier_(GLSL)
	glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, 1, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexColour");
	return true;
}

void Material::bindProgram()
{
	glUseProgram(m_ShaderProgram);
}

void Material::destroy()
{
	glDeleteProgram(m_ShaderProgram);
}

GLint Material::getUniformLocation(const std::string& variableName)
{
	return glGetUniformLocation(m_ShaderProgram, variableName.c_str());
}