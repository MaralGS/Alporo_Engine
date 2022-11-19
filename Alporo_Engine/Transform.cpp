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


	/*mat4x4& mat4x4::rotate(float angle, const vec3 & u)
	{
		angle = angle / 180.0f * (float)M_PI;

		vec3 v = normalize(u);

		float c = 1.0f - cos(angle), s = sin(angle);

		M[0] = 1.0f + c * (v.x * v.x - 1.0f);
		M[1] = c * v.x * v.y + v.z * s;
		M[2] = c * v.x * v.z - v.y * s;
		M[4] = c * v.x * v.y - v.z * s;
		M[5] = 1.0f + c * (v.y * v.y - 1.0f);
		M[6] = c * v.y * v.z + v.x * s;
		M[8] = c * v.x * v.z + v.y * s;
		M[9] = c * v.y * v.z - v.x * s;
		M[10] = 1.0f + c * (v.z * v.z - 1.0f);

		return *this;
	}*/

	//LOG(LogType::LOGS,"0: %d, 1: %d, 2: %d, 3: %d, ",Transform_Matrix[0] );
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
	Transform_Matrix[2] = sin(rotate.z);
	Transform_Matrix[6] = -sin(rotate.x);
	Transform_Matrix[10] = cos(rotate.z);
}

void Transform::MatRotZ()
{
	//rotacion en Z
	Transform_Matrix[0] = cos(rotate.x);
	Transform_Matrix[1] = -sin(rotate.y);
	Transform_Matrix[5] = sin(rotate.x);
	Transform_Matrix[6] = cos(rotate.y);


}



