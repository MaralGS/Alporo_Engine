#pragma once
#include "Module.h"
#include "Globals.h"
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"
#include "Component.h"

#include <string>
using namespace std;

class GameObject;
class Transform;

struct MyMesh {
	MyMesh();
	~MyMesh();

	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;
	GameObject* OBmesh = nullptr;
	void Render();
};

class ModuleLoadFBX : public Module
{
public:

	ModuleLoadFBX(Application* app, bool start_enabled = true);

	bool Start();
	GameObject* LoadFile(string file_path);
	void LoadMesh(MyMesh* mesh);

	update_status PostUpdate(float dt);
	//bool Init();
	bool CleanUp();
	bool FBX1 = true;
	bool FBX2 = true;
	bool FBX3 = true;
	GameObject* MeshObject = nullptr;

private:
	vector<MyMesh*> meshes;

};