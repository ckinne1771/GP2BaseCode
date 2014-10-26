#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "Game/Component.h"

class Mesh:public Component
{
public: 
	Mesh();
	~Mesh();

	void createBuffers();

	void destroy();

	void copyVertexData(int count,int stride, void ** data); 
	void copyIndexData(int count,int stride, void **data);
private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	int m_VertexCount;
	int m_IndexCount;
};

#endif