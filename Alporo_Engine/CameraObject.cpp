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
	VMatrix = mat4x4(NewCamera->X.x, NewCamera->X.x, NewCamera->X.x, 0.0f, NewCamera->X.y, NewCamera->X.y, NewCamera->X.y, 0.0f, NewCamera->X.z, NewCamera->X.z, NewCamera->X.z, 0.0f, -dot(NewCamera->X, NewCamera->Position), -dot(NewCamera->Y, NewCamera->Position), -dot(NewCamera->Z, NewCamera->Position), 1.0f);
	VMatrixInverse = inverse(VMatrix);
}