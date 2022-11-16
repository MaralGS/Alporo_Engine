#include "Component.h"

Component::Component(GameObject* Object)
{
	type = Type::None;
	principal = Object;
}

Component::~Component()
{
}

void Component::Inspector()
{

}
