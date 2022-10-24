#pragma once

class GameObject;

class Component
{
public:
	enum class Type
	{
		None,
		Transform,
		MeshRenderer,
		Rescale,
	};
	Component(GameObject* Object);
	~Component();
	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	bool active;
};
