#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"
#include "scene.h"
#include <vector>
#include "ModuleCFF.h"
#include "PhysFS/include/physfs.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

FileSystemProperties::FileSystemProperties()
{

}

FileSystemProperties* FileSystemProperties::Instance()
{
	if (instance == nullptr) instance = new FileSystemProperties();

	return instance;
}

void FileSystemProperties::Delete()
{
	if (instance != nullptr)
	{
		//RELEASE(instance);
	}
}


FileSystemProperties* FileSystemProperties::instance = nullptr;
#pragma endregion File System Properties singleton struct

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleFileSystem::~ModuleFileSystem()
{

}

bool ModuleFileSystem::Init()
{
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);



	meshImp = new MeshImporter();
	textImp = new TextureImporter();

	fsProps = FileSystemProperties::Instance();
	sProps = SceneProperties::Instance();

	fsProps->rootFolder = new LibraryFolder("Library", "Library", nullptr);
	LibraryManager::Init(*fsProps->rootFolder);

	return true;
}

bool ModuleFileSystem::Start()
{
	bool ret = true;


	meshImp->Init();

	return ret;
}

bool ModuleFileSystem::CleanUp()
{
	bool ret = true;
	/*
	LibraryManager::CleanUp();

	meshImp->CleanUp();

	if (fsProps->rootFolder != nullptr) RELEASE(fsProps->rootFolder);
	RELEASE(fsProps);

	RELEASE(meshImp);
	RELEASE(textImp);
	*/
	return ret;
}

update_status ModuleFileSystem::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleFileSystem::Update()
{


	return UPDATE_CONTINUE;
}

update_status ModuleFileSystem::PostUpdate()
{


	return UPDATE_CONTINUE;
}



