#include "CameraObject.h"

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

