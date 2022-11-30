#pragma once
#include<vector>
#include<string>

#include "Component.h"
#include "imgui.h"

enum class ComponentType;
class Transform;
class Meshes;

class GameObject 
{
	public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void CreateInspector();

	void MoveGameObject(GameObject* P);
	std::string name;
	GameObject* Parent;
	std::vector<GameObject*> child;
	std::vector<Component*> Comp;
	Transform* transform;
	Meshes* GOMesh;
	char Title[150] = "";
};