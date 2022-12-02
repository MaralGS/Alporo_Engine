#include "Transform.h"

Transform::Transform() 
{

}

Transform::Transform(GameObject* Transform) : Component(Transform)
{
	GObjectSelected = Transform;

	type = Type::Transform;
}

Transform::~Transform()
{
}

void Transform::Inspector()
{
	ImGui::Text("position");
	ImGui::InputFloat3("p", &position);
	ImGui::Text("Scale:");
	ImGui::InputFloat3("s",&scale);
	ImGui::Text("Rotation:");
	ImGui::InputFloat3("r", &rotate);
	Tranformation();
}

void Transform::Tranformation()
{


	Transform_Matrix.translate(position.x, position.y, position.z);


	Transform_Matrix.scale(scale.x, scale.y, scale.z);

}