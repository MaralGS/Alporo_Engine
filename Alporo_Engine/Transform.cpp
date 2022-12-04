#include "Transform.h"
#include "Mesh.h"

Transform::Transform() 
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

	//rotation
	Transform_Matrix[0][0] = (cos(Z) * cos(Y)) * (scale.x);// *scale.x);
	Transform_Matrix[0][1] = cos(Z) * sin(Y);
	Transform_Matrix[0][2] = -sin(Z);
	Transform_Matrix[3][0] = position.x;

	Transform_Matrix[1][0] =  (-cos(X) * sin(Z)) + ((sin(Y) * sin(Z) * cos(X)));
	Transform_Matrix[1][1] = ((sin(Y) * sin(Z) * sin(X)) + (cos(X) * cos(Z))) * (scale.y);// * scale.y);
	Transform_Matrix[1][2] = sin(Y) * cos(X);
	Transform_Matrix[3][1] = position.y;

	Transform_Matrix[2][0] = (cos(Z) * sin(Y) * cos(X)) + (sin(Z) * sin(X));
	Transform_Matrix[2][1] = (cos(X) * sin(Z) * sin(Y)) + (-sin(X) * cos(Z));
	Transform_Matrix[2][2] = (cos(X) * cos(Y)) * (scale.z);// *scale.z);
	Transform_Matrix[3][2] = position.z;
}