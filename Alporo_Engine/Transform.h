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


	aiVector3D Translation, Scaling;
	aiQuaternion rotation;
	aiNode* node;


	mat4x4 Transform_Matrix;
	vec3 position;
	vec3 scale;
	vec3 rotate;
private:

};
