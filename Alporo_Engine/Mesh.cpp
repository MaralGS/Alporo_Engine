#include "Mesh.h"

Meshes::Meshes() : Meshes(nullptr)
{

}

Meshes::Meshes(GameObject* Principal) : Component(Principal)
{
	principal = Principal;
	mesh = nullptr;
}

Meshes::~Meshes()
{
	principal = nullptr;
	mesh = nullptr;
}

