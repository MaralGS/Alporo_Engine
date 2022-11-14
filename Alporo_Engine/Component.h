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
	bool active;
	Type type;
	GameObject* principal;
	
};
