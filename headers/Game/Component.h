#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
public:
	Component()
	{
		m_Name = "BaseComponent";
		m_Type = "BaseComponent";
	};

	virtual ~Component(){};

	const std::string& getName()
	{
		return m_Name;
	};

	const std::string& getType()
	{
		return m_Type;
	};

	void setParent(GameObject *parent)
	{
		m_Parent = parent;
	}; 

	//Will be overriden
	virtual void init(){};
	virtual void update(){};
	virtual void render(){};
	virtual void destroy(){};
protected:
	std::string m_Name;
	std::string m_Type;
	GameObject *m_Parent;
};

#endif