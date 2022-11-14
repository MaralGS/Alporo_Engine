#include "GameObject.h"

GameObject::GameObject()
{
	name = "hola";
	Parent = nullptr;
}

GameObject::GameObject(GameObject* parent)
{
	name = "hola";
	Parent = parent;

	if (parent != nullptr)
	{
		parent->child.push_back(this);
	}
}

GameObject::~GameObject()
{
	name = nullptr;
	Parent = nullptr;
	
}

void GameObject::CreateInspector()
{
	if (ImGui::Begin("Inspector")) {
		if (ImGui::CollapsingHeader("Inspector"))
		{

		}
	}
	ImGui::End();
}


