#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"




class ModuleImguiWindow : public Module
{
public:
	ModuleImguiWindow(Application* app, bool start_enabled = true);
	~ModuleImguiWindow();

	bool Start();
	bool PostUpdate();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	bool ActiveDemo = false;

	bool CloseApp = false;
private:

};

