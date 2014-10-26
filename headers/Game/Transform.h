#ifndef TRANSFORM_H
#define TRANSFROM_H

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;

class Transform :public Component
{
public:
	Transform();
	~Transform();
	void init(){};
	void update();
	void render(){};

	void setPosition(float x, float y, float z)
	{
		m_Position = vec3(x, y, z);
	};

	const vec3& getPosition()
	{
		return m_Position;
	};

	void setRotation(float x, float y, float z)
	{
		m_Rotation = vec3(x, y, z);
	};

	const vec3& getRotation()
	{
		return m_Rotation;
	};

	void setScale(float x, float y, float z)
	{
		m_Scale = vec3(x, y, z);
	};

	const vec3& getScale()
	{
		return m_Scale;
	}

	const mat4& getModel()
	{
		return m_Model;
	};
private:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
	mat4 m_Model;
};

#endif