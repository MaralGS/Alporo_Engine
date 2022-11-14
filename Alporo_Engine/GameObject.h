#pragma once
#include<vector>
#include<string>

#include "Component.h"
#include "imgui.h"


class GameObject 
{
	public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void CreateInspector();
	std::string name;
	GameObject* Parent;
	std::vector<GameObject*> child;
	std::vector<Component*> Comp;

};