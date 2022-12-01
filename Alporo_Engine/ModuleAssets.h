#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleAssets : public Module
{
public:
	ModuleAssets(Application* app, bool start_enabled = true);
	~ModuleAssets();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();

private:

};



