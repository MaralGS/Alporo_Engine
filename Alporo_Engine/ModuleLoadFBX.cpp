#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <gl/GL.h>


ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleLoadFBX::~ModuleLoadFBX()
{

}


bool ModuleLoadFBX::Start()
{
	file_path = ("Assets/Ganivet.fbx");
	LOG("Loading Intro assets");
	bool ret = true;

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	
	scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		
		aiReleaseImport(scene);
	}
	else{
		
	}
	return ret;
}

bool ModuleLoadFBX::PreUpdate() 
{

	return true;
}

update_status ModuleLoadFBX::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleLoadFBX::PostUpdate() {



	return true;
}

void ModuleLoadFBX::LoadMesh(aiMesh* MyMesh)
{
	MyMesh->mNumVertices = scene->mMeshes->mNumVertices;
	mymesh->mVertices = new aiVector3D[mymesh->mNumVertices * 3];
	memcpy(mymesh->mVertices, mesh->mVertices, sizeof(aiVector3D) * mymesh->mNumVertices * 3);
}

bool ModuleLoadFBX::CleanUp()
{
	aiDetachAllLogStreams();
	LOG("Unloading Intro scene");
	return true;
}

