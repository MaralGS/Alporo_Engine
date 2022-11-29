#pragma once
#include "Module.h"

class MeshImporter;
class TextureImporter;
class LibraryFolder;

struct SceneProperties;

struct FileSystemProperties
{
public:
	FileSystemProperties();

	static FileSystemProperties* Instance();

	static void Delete();

public:
	LibraryFolder* rootFolder;
private:
	static FileSystemProperties* instance;
};

class ModuleFileSystem : public Module
{
public:
	ModuleFileSystem(Application* app, bool start_enabled = true);
	~ModuleFileSystem();

	bool Init() override;
	bool Start() override;

	bool CleanUp() override;

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();


public:
	FileSystemProperties* fsProps = nullptr;
	SceneProperties* sProps = nullptr;

	MeshImporter* meshImp = nullptr;
	TextureImporter* textImp = nullptr;
};

