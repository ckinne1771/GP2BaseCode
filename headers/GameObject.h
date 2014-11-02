//
//  GameObject.h
//  GP2BaseCode
//
//  Created by Brian on 31/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include <string>
#include <vector>

class Component;
class Transform;
class Mesh;
class Material;
class Camera;

class GameObject
{
public:
    GameObject();
    ~GameObject();
    
    void init();
    
    void update();
    
    void render();
    
    void destroy();
    
    void addComponent(Component * component);
    void setName(const std::string& name);
    const std::string& getName();
    
    void setTransform(Transform * transform);
    void setMesh(Mesh * mesh);
    void setMaterial(Material * material);
    void setCamera(Camera * camera);
	void addChild(GameObject * obj);
	void setParent(GameObject *parent);
    
	GameObject *getParent();

	Transform * getTransform();
    Mesh *getMesh();
    Material *getMaterial();
    Camera * getCamera();

	int getChildCount();
	GameObject * getChild(int index);

    

protected:
private:
    std::vector<Component*> m_Components;
	std::vector<GameObject*> m_Children;
	std::string m_Name;
    
    Transform *m_Transform;
    Mesh *m_Mesh;
    Material *m_Material;
    Camera *m_Camera;

	GameObject *m_Parent;
};


#endif
