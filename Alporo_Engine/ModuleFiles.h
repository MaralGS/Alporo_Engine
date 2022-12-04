#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )


struct FileInfo {
	FileInfo(string path);
	string path;
	string name;
	bool folder;
};

class ModuleFiles : public Module
{
public:

	ModuleFiles(Application* app, bool start_enabled = true);
	~ModuleFiles();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void RemoveFile(FileInfo file);

	void SetCurrentPath(const char* path);

private:

	void PrintFiles();
	void PrintPathBar();

	//Change FilesDir variable
	void GetDirectoryInfo(const char* dir);

	bool Reload;

	string currentPath;
	vector<FileInfo> directionFiles;

	string pathName;
	string fileName;

	bool DeleteOption = false;
	bool CreateFolderBool = false;
};
