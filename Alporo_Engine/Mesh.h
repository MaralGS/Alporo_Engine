#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "glmath.h"
#include "imgui.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"

class GameObject;
class Component;
struct MyMesh;

class Meshes : public Component
{
public:
	Meshes();
	Meshes(GameObject* Meshobject);
	~Meshes();

	void Inspector();

	MyMesh* mesh;
};


