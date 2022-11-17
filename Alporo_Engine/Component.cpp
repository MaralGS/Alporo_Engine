#include "Component.h"

Component::Component(GameObject* Object)
{
	type = Type::None;
	GObjectSelected = Object;
}

Component::~Component()
{
}

void Component::Inspector()
{

}
