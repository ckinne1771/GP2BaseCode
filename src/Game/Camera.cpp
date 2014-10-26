#include "Game\Camera.h"

#include "Game\GameObject.h"
#include "Game\Transform.h"

Camera::Camera()
{
	m_Type = "Camera";
	m_LookAt=vec3(0.0f,0.0f,0.0f);
	m_Up=vec3(0.0f,1.0f,0.0f);
	m_NearClip=0.1f;
	m_FarClip = 100.0f;
	m_FOV=45.0f;	
	m_AspectRatio=16.0f/9.0f;
	m_isOrthogrpahic=false;
	m_View = mat4();
	m_Projection = mat4();
}

Camera::~Camera()
{

}

void Camera::update()
{
	//get the position from the transform
	vec3 position = m_Parent->getTransform()->getPosition();

	m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	m_View = glm::lookAt(position, m_LookAt, m_Up);
}