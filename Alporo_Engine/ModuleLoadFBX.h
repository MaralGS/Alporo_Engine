#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "scene.h"
#include "cimport.h"
#include "postprocess.h"

using std::vector;

class ModuleLoadFBX : public Module
{
public:
	ModuleLoadFBX(Application* app, bool start_enabled = true);
	~ModuleLoadFBX();

	bool Start();
	bool PostUpdate();
	update_status Update(float dt);
	bool PreUpdate();
	bool CleanUp();
	void LoadMesh(aiMesh* MyMesh);
	const vector<ModuleLoadFBX*> MyMesh;
	
private:
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	const aiScene* scene;
	const char* file_path;

};

