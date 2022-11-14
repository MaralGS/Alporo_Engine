#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "glmath.h"
#include "imgui.h"

class Transform : public Component
{
public:
	Transform();
	Transform(GameObject* Principal);
	~Transform();

	void Inspector();

	vec3 position;
	vec3 scale;
	vec3 rotate;

};
