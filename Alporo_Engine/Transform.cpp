#include "Transform.h"

Transform::Transform() : Component(nullptr)
{

}

Transform::Transform(GameObject* Transform) : Component(Transform)
{
	GObjectSelected = Transform;
	/*position = {Translation.x, Translation.y, Translation.z};
	scale = { Scaling.x,Scaling.y,Scaling.z };
	rotate = { rotation.x, rotation.y, rotation.z };*/

	position = { 0,0,0 };
	scale = { 0,0,0 };
	rotate = { 1,1,1 };

	type = Type::Transform;
	Transform_Matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

Transform::~Transform()
{
}

void Transform::Inspector()
{
	ImGui::Text("position");
	ImGui::InputFloat3("", &position);
	ImGui::Text("Scale:");
	ImGui::InputFloat3("", & scale);
	ImGui::Text("Rotation:");
	ImGui::InputFloat3("", &rotate);
	Tranformation();
	//Tranformation();
}

void Transform::Tranformation()
{
	node->mTransformation.Decompose(Scaling, rotation, Translation);

	float3 pos(Translation.x, Translation.y, Translation.z);
	float3 scale(Scaling.x, Scaling.y, Scaling.z);
	Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);


}

