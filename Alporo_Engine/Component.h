#pragma once

class GameObject;

enum class Type
{
	None,
	Transform,
	MeshRenderer,
	Rescale,
};

class Component
{
public:

	Component(GameObject* Object);
	~Component();

	virtual void Inspector();
	bool active;
	Type type;
	GameObject* principal = nullptr;

};

