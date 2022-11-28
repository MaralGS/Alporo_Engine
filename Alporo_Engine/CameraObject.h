#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"


class GameObject;
class Component;
struct Camera;

class CObject : public Component
{
public:
	CObject();
	CObject(GameObject* CObject);
	~CObject();

	void Update();

	void Inspector();

	Camera* NewCamera = nullptr;
	GameObject* GMCamera = nullptr;
};


