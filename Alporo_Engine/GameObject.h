#pragma once
#include<vector>
#include<string>

#include "Component.h"
class GameObject 
{
	GameObject();
	~GameObject();
	void Update();
	Component* CreateComponent(Component::Type type);
	std::string name;
	std::vector<Component*> components;

};