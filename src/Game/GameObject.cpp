#include "Game\GameObject.h"
#include "Game\Component.h"
#include "Game\Transform.h"
#include "Game\Material.h"
#include "Game\Mesh.h"


GameObject::GameObject()
{
	m_Transform = new Transform();
	addComponent(m_Transform);
}

GameObject::~GameObject()
{
	destroy();
}

void GameObject::addComponent(Component * component)
{
	component->setParent(this);
	m_Components.push_back(component);
};

void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
	for (auto iter = m_ChildGameObjects.begin(); iter != m_ChildGameObjects.end(); iter++)
	{
		(*iter)->init();
	}
}

void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
	for (auto iter = m_ChildGameObjects.begin(); iter != m_ChildGameObjects.end(); iter++)
	{
		(*iter)->update();
	}
}

void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
	for (auto iter = m_ChildGameObjects.begin(); iter != m_ChildGameObjects.end(); iter++)
	{
		(*iter)->render();
	}
}

void GameObject::destroy()
{
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			delete (*iter);
			(*iter) = NULL;
			iter = m_Components.erase(iter);
		}
		iter++;
	}
	auto gameObjectIter = m_ChildGameObjects.begin();
	while (gameObjectIter != m_ChildGameObjects.end())
	{
		if ((*gameObjectIter))
		{
			(*gameObjectIter)->destroy();
			delete (*gameObjectIter);
			(*gameObjectIter) = NULL;
			gameObjectIter = m_ChildGameObjects.erase(gameObjectIter);
		}
		gameObjectIter++;
	}
}

void GameObject::setMaterial(Material * mat)
{
	m_Material = mat;
	addComponent(mat);
}

void GameObject::setMesh(Mesh * mesh)
{
	m_Mesh = mesh;
	addComponent(mesh);
}