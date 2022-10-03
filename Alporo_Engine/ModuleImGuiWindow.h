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
	IMGUI_API void          ShowWindow(bool* p_open = NULL);
	bool PostUpdate();

	update_status PreUpdate(float dt);
	bool CleanUp();
	
	//bools
	bool ActiveDemoWindows = true;
	bool AboutTxt = false;
	bool FullScreenEnable = false;
	bool CloseApp = false;

	//ints
	float BrightnessStart = 1.f;
	float BrightnessMin = 0.f;
	float BrightnessMax = 1.f;
private:

};

