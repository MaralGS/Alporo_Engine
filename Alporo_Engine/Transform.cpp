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
	ImGui::InputFloat3("", &position);
	/*ImGui::Text("Scale:");
	ImGui::InputFloat3("", & scale);
	ImGui::Text("Rotation:");
	ImGui::InputFloat3("", &rotate);*/
	Tranformation();
}

void Transform::Tranformation()
{

	//position.x = position.x * MatRotX();
	MatRotX();
	MatRotY();
	MatRotZ();
	Transform_Matrix[4] = position.x;
	Transform_Matrix[8] = position.y;
	Transform_Matrix[12] = position.z;
}

void Transform::MatRotX()
{
	//rotacion en x
	Transform_Matrix[6] = cos(rotate.y);
	Transform_Matrix[7] = -sin(rotate.z);
	Transform_Matrix[10] = sin(rotate.y);
	Transform_Matrix[11] = cos(rotate.z);
}

void Transform::MatRotY()
{
	//rotacion en y
	Transform_Matrix[0] = cos(rotate.x);
	Transform_Matrix[3] = sin(rotate.z);
	Transform_Matrix[9] = -sin(rotate.x);
	Transform_Matrix[11] = cos(rotate.z);
}

void Transform::MatRotZ()
{
	//rotacion en Z
	Transform_Matrix[0] = cos(rotate.x);
	Transform_Matrix[1] = -sin(rotate.y);
	Transform_Matrix[5] = sin(rotate.x);
	Transform_Matrix[6] = cos(rotate.y);


}



