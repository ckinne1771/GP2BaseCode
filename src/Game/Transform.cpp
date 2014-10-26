#include "Game\Transform.h"
#include "Game\GameObject.h"

Transform::Transform()
{
	m_Position=vec3(0.0f,0.0f,0.0f);
	m_Rotation=vec3(0.0f,0.0f,0.0f);
	m_Scale=vec3(1.0f,1.0f,1.0f);
	m_Model=mat4();
	m_Type = "Transform";
}

Transform::~Transform()
{

}

//calculate the model matrix
void Transform::update()
{
	mat4 translate = glm::translate(translate, m_Position);
	mat4 scale = glm::scale(scale, m_Scale);

	mat4 rotationX = glm::rotate(rotationX, m_Rotation.x, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationY = glm::rotate(rotationY, m_Rotation.y, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZ = glm::rotate(rotationZ, m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotation = rotationX*rotationY*rotationZ;

	m_Model = rotation*scale*translate;
	if (m_Parent)
	{
		m_Model *= m_Parent->getTransform()->getModel();
	}
}