#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

class Transform;
class Material;
class Mesh;
class Camera;
class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	
	void init();
	void update();
	void render();
	void destroy();

	Transform * getTransform()
	{
		return m_Transform;
	};

	Material * getMaterial()
	{
		return m_Material;
	};

	Mesh * getMesh()
	{
		return m_Mesh;
	};

	void setMaterial(Material * mat);
	void setMesh(Mesh * mesh);
	void setCamera(Camera *camera);

	void addComponent(Component * component);

	void addChild(GameObject * child)
	{
		m_ChildGameObjects.push_back(child);
	};

	std::vector<GameObject*>::iterator getFirstChild()
	{
		return m_ChildGameObjects.begin();
	};

	std::vector<GameObject*>::iterator getLastChild()
	{
		return m_ChildGameObjects.end();
	};

private:
	std::vector<Component*> m_Components;
	std::vector<GameObject*> m_ChildGameObjects;
	Transform *m_Transform;
	Material * m_Material;
	Mesh *m_Mesh;
	Camera *m_Camera;

};
#endif