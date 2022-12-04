#include "Transform.h"
#include "Mesh.h"

Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* Transform) : Component(Transform)
{
	GObjectSelected = Transform;

	type = Type::Transform;
	Transform_Matrix = float4x4::identity;
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
	float X = rotate.x * DEGTORAD;
	float Y = rotate.y * DEGTORAD;
	float Z = rotate.z * DEGTORAD;
	
	Transform_Matrix[0][0] = cos(Z) * cos(X) * scale.x;
	Transform_Matrix[0][1] = cos(Z) * sin(X);
	Transform_Matrix[0][2] = -sin(Z);
	Transform_Matrix[0][3] = 0;


	Transform_Matrix[1][0] = -cos(Y) * sin(X) + sin(Z) * cos(X) * sin(Y);
	Transform_Matrix[1][1] = (cos(Y) * cos(X) + sin(Z) * sin(X) * sin(Y)) * scale.y;
	Transform_Matrix[1][2] = sin(Y) * cos(Z);
	Transform_Matrix[1][3] = 0;

	Transform_Matrix[2][0] = sin(X) * sin(Y) + cos(X) * sin(Z) * cos(Y);
	Transform_Matrix[2][1] = -sin(Y) * cos(X) + cos(Y) * sin(X) * sin(Z);
	Transform_Matrix[2][2] = cos(Z) * cos(Y) * scale.z;  
	Transform_Matrix[2][3] = 0;

	Transform_Matrix[3][0] = position.x;
	Transform_Matrix[3][1] = position.y;
	Transform_Matrix[3][2] = position.z;
	Transform_Matrix[3][3] = 1;



	//rotation
	//Transform_Matrix[0][0] = cos(X) * cos(Z) * scale.x;
	//Transform_Matrix[0][1] = cos(X) * sin(Z);
	//Transform_Matrix[0][2] = -sin(X);
	//Transform_Matrix[0][3] = 0;
	//
	//
	//Transform_Matrix[1][0] = -cos(Y) * sin(Z) + sin(X) * cos(Z) * sin(Y);
	//Transform_Matrix[1][1] = cos(Y) * cos(Z) + sin(X) * sin(Z) * sin(Y) * scale.y;
	//Transform_Matrix[1][2] = sin(Y) * cos(X);
	//Transform_Matrix[1][3] = 0;
	//
	//Transform_Matrix[2][0] = sin(Z) * sin(Y) + cos(Z) * sin(X) * cos(Y);
	//Transform_Matrix[2][1] = -sin(Y) * cos(Z) + cos(Y) * sin(Z) * sin(X);
	//Transform_Matrix[2][2] = cos(X) * cos(Y) * scale.z;
	//Transform_Matrix[2][3] = 0;
	//
	//Transform_Matrix[3][0] = position.x;
	//Transform_Matrix[3][1] = position.y;
	//Transform_Matrix[3][2] = position.z;
	//Transform_Matrix[3][3] = 1;

}