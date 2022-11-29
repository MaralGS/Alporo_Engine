#include "Transform.h"

Transform::Transform() : Component(nullptr)
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

	//rotation
	Transform_Matrix[0] = cos(rotate.z) * cos(rotate.x);
	Transform_Matrix[4] = cos(rotate.z) * sin(rotate.x);
	Transform_Matrix[8] = -sin(rotate.z);

	Transform_Matrix[1] = (sin(rotate.y) * sin(rotate.z) * cos(rotate.x)) - (cos(rotate.y) * sin(rotate.x));
	Transform_Matrix[5] = (sin(rotate.y) * sin(rotate.z) * sin(rotate.x)) + (cos(rotate.y) * cos(rotate.x));
	Transform_Matrix[9] = sin(rotate.y) * cos(rotate.z);


	Transform_Matrix[2] = (cos(rotate.y) * sin(rotate.z) * cos(rotate.x)) + (sin(rotate.y) * sin(rotate.x));
	Transform_Matrix[6] = (cos(rotate.y) * sin(rotate.z) * sin(rotate.x)) - (sin(rotate.y) * cos(rotate.x));
	Transform_Matrix[10] = cos(rotate.y) * cos(rotate.z);



}