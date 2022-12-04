#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "imgui.h"
#include "Application.h"


class GameObject;
class Component;
class aiNode;

class Transform : public Component
{
public:
	Transform();
	Transform(GameObject* Transform);
	~Transform();

	void Inspector();
	void Tranformation();

	float4x4 Transform_Matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float3 position = { 0,0,0 };
	float3 scale = { 1,1,1 };
	float3 rotate = {0,0,0};
	float angle = 180;

private:

};
