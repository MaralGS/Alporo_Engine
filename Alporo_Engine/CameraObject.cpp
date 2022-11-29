#include "CameraObject.h"
#include "ModuleCamera3D.h"
#include "glmath.h"

CObject::CObject() : Component(nullptr)
{

}

CObject::CObject(GameObject* CameraObj) : Component(CameraObj)
{
	GObjectSelected = CameraObj;
	type = Type::CamObject;
}

CObject::~CObject()
{
	GObjectSelected = nullptr;
}

void CObject::Update()
{
	vec3 newPos(0, 0, 0);
	NewCamera->Position += newPos;
	NewCamera->Reference += newPos;

	CalculateVMatrix();
}


void CObject::CalculateVMatrix()
{
	//VMatrix = mat4x4(NewCamera->X.x, NewCamera->X.x, NewCamera->X.x, 0.0f, NewCamera->X.y, NewCamera->X.y, NewCamera->X.y, 0.0f, NewCamera->X.z, NewCamera->X.z, NewCamera->X.z, 0.0f, -dot(NewCamera->X, NewCamera->Position), -dot(NewCamera->Y, NewCamera->Position), -dot(NewCamera->Z, NewCamera->Position), 1.0f);
	//VMatrixInverse = inverse(VMatrix);
}

void CObject::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{
	
	NewCamera->Position = Position;
	NewCamera->Reference = Reference;

	NewCamera->Z = normalize(Position - Reference);
	NewCamera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), NewCamera->Z));
	NewCamera->Y = cross(NewCamera->Z, NewCamera->X);

	if (!RotateAroundReference)
	{
		NewCamera->Reference = NewCamera->Position;
		NewCamera->Position += NewCamera->Z * 0.05f;
	}

	CalculateVMatrix();
}

void CObject::LookAt(const vec3& Spot)
{
	NewCamera->Reference = Spot;

	NewCamera->Z = normalize(NewCamera->Position - NewCamera->Reference);
	NewCamera->X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), NewCamera->Z));
	NewCamera->Y = cross(NewCamera->Z, NewCamera->X);

	CalculateVMatrix();
}

void CObject::Move(const vec3& Movement)
{
	NewCamera->Position += Movement;
	NewCamera->Reference += Movement;

	CalculateVMatrix();
}

float* CObject::GetViewMatrix()
{

	return nullptr;
}
