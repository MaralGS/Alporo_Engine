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
	void CalculateVMatrix();


	Camera* NewCamera = nullptr;
	GameObject* GMCamera = nullptr;
	mat4x4 VMatrix, VMatrixInverse;
private:

};


