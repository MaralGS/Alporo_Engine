#include "Transform.h"
#include "Mesh.h"

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
	//ImGui::InputText("name:", &GObjectSelected->GOMesh->mesh->OBmesh->name);
	ImGui::Text("position");
	ImGui::InputFloat3("p", position.ptr());
	ImGui::Text("Scale:");
	ImGui::InputFloat3("s", scale.ptr());
	ImGui::Text("Rotation:");
	ImGui::InputFloat3("r", rotate.ptr());
	Tranformation();
}

void Transform::Tranformation()
{
	//rotation
	Transform_Matrix[0][0] = (cos(rotate.z) * cos(rotate.x)) * (scale.x * scale.x) ;
	Transform_Matrix[3][0] = cos(rotate.z) * sin(rotate.x);
	Transform_Matrix[0][2] = -sin(rotate.z);
	Transform_Matrix[3][0] = position.x;

	Transform_Matrix[1][0] = (sin(rotate.y) * sin(rotate.z) * cos(rotate.x)) - (cos(rotate.y) * sin(rotate.x));
	Transform_Matrix[1][1] = ((sin(rotate.y) * sin(rotate.z) * sin(rotate.x)) + (cos(rotate.y) * cos(rotate.x))) * (scale.y * scale.y);
	Transform_Matrix[1][2] = sin(rotate.y) * cos(rotate.z);
	Transform_Matrix[3][1] = position.y;


	Transform_Matrix[2][0] = (cos(rotate.y) * sin(rotate.z) * cos(rotate.x)) + (sin(rotate.y) * sin(rotate.x));
	Transform_Matrix[2][1] = (cos(rotate.y) * sin(rotate.z) * sin(rotate.x)) - (sin(rotate.y) * cos(rotate.x));
	Transform_Matrix[2][2] = (cos(rotate.y) * cos(rotate.z)) * (scale.z * scale.z);
	Transform_Matrix[3][2] = position.z;
}