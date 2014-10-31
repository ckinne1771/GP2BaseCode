//
//  Material.c
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "Material.h"
#include "Shader.h"

Material::Material()
{
	m_ShaderProgram = -1;
	m_Type = "Material";
}

Material::~Material()
{
    
}

void Material::destroy()
{
    glDeleteProgram(m_ShaderProgram);
}

void Material::bind()
{
    glUseProgram(m_ShaderProgram);
}

bool Material::loadShader(const std::string& vsFilename,const std::string& fsFilename)
{
    GLuint vertexShaderProgram=0;
	vertexShaderProgram = loadShaderFromFile(const_cast<std::string&>(vsFilename), VERTEX_SHADER);
    
    GLuint fragmentShaderProgram=0;
	fragmentShaderProgram = loadShaderFromFile(const_cast<std::string&>(fsFilename), FRAGMENT_SHADER);
    
    m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
    
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
    
    glBindAttribLocation(m_ShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram,1, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, 2, "vertexColour");

    return true;
}

GLint Material::getUniformLocation(const std::string& name)
{
    return glGetUniformLocation(m_ShaderProgram, name.c_str());
}
