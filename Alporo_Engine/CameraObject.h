#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"


class GameObject;
class Component;

class CObject : public Component
{
public:
	CObject();
	CObject(GameObject* CObject);
	~CObject();


};


