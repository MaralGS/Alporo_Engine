#pragma once
#include<vector>
#include<string>
#include<map>

#include "Component.h"
#include "Globals.h"
class GameObject 
{
	GameObject();
	~GameObject();
	void Update();
	Component* CreateComponent(Component::Type type);
	std::string name;
	std::vector<Component*> components;

	GameObject* rootNodeGO = nullptr;

	std::map <uint, GameObject*> GObject;
	std::map <uint, GameObject*>* GObjectChild;

};