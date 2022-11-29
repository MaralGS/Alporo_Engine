#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"
#include "scene.h"
#include <vector>
#include "ModuleCFF.h"
#include "PhysFS/include/physfs.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

bool MoudleCFF::Start()
{
	return false;
}

const char* MoudleCFF::MeshSave(MyMesh* mesh)
{
	mesh->num_indices;
	uint ranges[2] = { mesh->num_indices, mesh->num_vertices };
	uint size = sizeof(ranges) + sizeof(uint) * mesh->num_indices + sizeof(float) * mesh->num_vertices * 3;
	char* fileBuffer = new char[size]; 
	char* cursor = fileBuffer;
	uint bytes = sizeof(ranges); 

	memcpy(cursor, ranges, bytes);
	cursor += bytes;

	// Store indices
	bytes = sizeof(uint) * mesh->num_indices;
	memcpy(cursor, mesh->indices, bytes);
	cursor += bytes;

	// Store vertices
	bytes = sizeof(float) * mesh->num_vertices;
	memcpy(cursor, mesh->vertices, bytes);
	cursor += bytes;

	return fileBuffer;
}



update_status MoudleCFF::PostUpdate(float dt)
{
	return update_status();
}

bool MoudleCFF::CleanUp()
{
	return false;
}
