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
	IMGUI_API bool          ShowWindow(bool* p_open = NULL);
	bool PostUpdate();

	bool PreUpdate();
	bool CleanUp();
	


	//bools
	bool ActiveDemoWindows = true;

	bool AboutTxt = false;
	bool FullScreenEnable = false;
	bool Dummy = false;
	bool CloseApp = false;

	//const char fps_log[60];
	//const char ms_log[60];
	//float
	float BrightnessStart = 1.f;
	float BrightnessMin = 0.f;
	float BrightnessMax = 1.f;
	
	//ints
	int WidthMin = 0;
	int WidthMax = 2040;
	int FPSStart = 0;
	int FPSMin = 0;
	int FPSMax = 120;

private:

};

