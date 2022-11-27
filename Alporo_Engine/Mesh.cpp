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


void Meshes::Update()
{
	
}


void Meshes::Inspector()
{
	ImGui::Text("Number Vertices: %d", mesh->num_vertices);
	ImGui::Text("Number Indices: %d", mesh->num_indices);
}

