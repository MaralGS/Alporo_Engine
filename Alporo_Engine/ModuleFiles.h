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
	string extension;
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

	void CreateFolder(const char* dir);
	void RemoveFile(FileInfo file);

	void SetCurrentPath(const char* path);

private:

	void PrintAssets();
	void PrintAssetsMenu();

	//Change dirInfo variable
	void GetDirectoryInfo(const char* dir);

	bool Refresh;

	string currentPath;
	vector<FileInfo> dirInfo;

	string pathToRename;
	string fileSelected;

	bool fileMenu = false;

	uint folderTexture;
	uint pngTexture;
	uint fbxTexture;
	uint elseTexture;
};
