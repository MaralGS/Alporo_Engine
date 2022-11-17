#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
	name = "root";
	Parent = nullptr;
	transform = new Transform(this);
	Comp.push_back(transform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "GameObject";
	Parent = parent;
	transform = new Transform(this);
	Comp.push_back(transform);

	//GOMesh = new Meshes(this);
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
		for (size_t i = 0; i < Comp.size(); i++)
		{
			Comp[i]->Inspector();
		}
	}
	ImGui::End();
}

