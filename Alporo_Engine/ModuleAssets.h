#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleAssets.h"

class ModuleAssets : public Module
{
public:
	ModuleAssets(Application* app, bool start_enabled = true);
	~ModuleAssets();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

public:
	GameObject* Root = nullptr;
};
