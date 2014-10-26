#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

//maths headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec3;

class Camera :public Component
{
public:
	Camera();
	~Camera();

	void update();

	void setLook(float x, float y, float z)
	{
		m_LookAt = vec3(x, y, z);
	};

	void setUp(float x, float y, float z)
	{
		m_Up = vec3(x, y, z);
	};
	/*
	void setNearClip(float near)
	{
		m_NearClip = near;
	};
	
	void setFarClip(float far)
	{
		m_FarClip = far;
	};
	*/
	void setFOV(float FOV)
	{
		m_FOV = FOV;
	};

	void setAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
	};
	
	mat4& getView()
	{
		return m_View;
	};

	mat4& getProjection()
	{
		return m_Projection;
	};

private:
	vec3 m_LookAt;
	vec3 m_Up;

	mat4 m_View;
	mat4 m_Projection;

	float m_NearClip;
	float m_FarClip;
	float m_FOV;
	float m_AspectRatio;
	bool m_isOrthogrpahic;

};

#endif