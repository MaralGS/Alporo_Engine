#include "Mesh.h"

Meshes::Meshes() : Meshes(nullptr)
{

}

Meshes::Meshes(GameObject* Meshobject) : Component(Meshobject)
{
	GObjectSelected = Meshobject;
	mesh = nullptr;
	type = Type::MeshRenderer;
}

Meshes::~Meshes()
{
	GObjectSelected = nullptr;
	mesh = nullptr;
}

void Meshes::Inspector()
{
	ImGui::Text("Number Verticles: %d", mesh->id_vertices);
}

