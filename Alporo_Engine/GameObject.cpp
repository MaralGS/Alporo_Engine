#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	/*for (int i = 0; i < length; i++)
	{

	}
	GObject[];*/
}

Component* GameObject::CreateComponent(Component::Type type)
{
	return nullptr;
}
