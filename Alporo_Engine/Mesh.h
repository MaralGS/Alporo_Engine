#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "glmath.h"
#include "imgui.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"

class Meshes : public Component
{
public:
	Meshes();
	Meshes(GameObject* MeshObject);
	~Meshes();

	void Inspector();

	MyMesh* mesh;
};


