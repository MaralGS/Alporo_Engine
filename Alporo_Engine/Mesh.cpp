#include "Mesh.h"

Meshes::Meshes() : Meshes(nullptr)
{

}

Meshes::Meshes(GameObject* MeshObject) : Component(MeshObject)
{
	GObjectSelected = MeshObject;
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
	//ImGui::Text("Number Verticles: %d", mesh->id_vertices);
}

