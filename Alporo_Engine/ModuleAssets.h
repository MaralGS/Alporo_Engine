#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleAssets.h"
#include "Resources.h"
#include <map>

class ModuleAssets : public Module
{
public:
	ModuleAssets(Application* app, bool start_enabled = true);
	~ModuleAssets();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	int Find(const char* file_in_assets) const;
	int ImportFile(const char* new_file_in_assets);
	int GenerateNewUID();
	const Resource* RequestResource(int uid) const;
	Resource* RequestResource(int uid);
	void ReleaseResource(int uid);
	private:
	Resource* CreateNewResource(const char* assetsFile, Resource::Type type);
	std::map<int, Resource*> resources;


public:
	GameObject* Root = nullptr;
};
