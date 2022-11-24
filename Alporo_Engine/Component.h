#pragma once

class GameObject;

enum class Type
{
	None,
	Transform,
	MeshRenderer,
};

class Component
{
public:

	Component(GameObject* Object);
	~Component();

	virtual void Inspector();
	bool active;
	Type type;
	GameObject* GObjectSelected = nullptr;

};

