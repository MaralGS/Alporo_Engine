#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "glmath.h"
#include "imgui.h"
#include "Application.h"
#include"MathGeoLib/include/Math/float3.h"
#include"MathGeoLib/include/Math/Quat.h"

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
	void MatRotX();
	void MatRotY();
	void MatRotZ();

	mat4x4 Transform_Matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	vec3 position = { 0,0,0 };
	vec3 scale = { 1,1,1 };
	vec3 rotate = { 1,1,1 };

private:

};
