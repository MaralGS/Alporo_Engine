#include "Component.h"

Component::Component()
{
	int hola = 0;
}

Component::Component(GameObject* Object)
{
	type = Type::None;
	GObjectSelected = Object;
}

Component::~Component()
{
}

void Component::Update()
{

}

void Component::GameCameraMovement(GameObject* CamObject)
{
	type = Type::None;
	GObjectSelected = CamObject;
}

void Component::Inspector()
{

}
