#include "Transform.h"

Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* Principal) : Component(Principal)
{
	principal = Principal;
	position = { 0,0,0 };
	scale = { 0,0,0 };
	rotate = { 1,1,1 };
}

Transform::~Transform()
{
}

void Transform::Inspector()
{
	ImGui::Text("X: %d Y: %d Z: %d position", position);
	ImGui::Text("X: %d Y: %d Z: %d Scale", scale);
	ImGui::Text("X: %d Y: %d Z: %d Rotation", rotate);
}

