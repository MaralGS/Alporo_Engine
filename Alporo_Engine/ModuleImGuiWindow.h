#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#include <vector>
class ModuleImguiWindow : public Module
{
public:
	ModuleImguiWindow(Application* app, bool start_enabled = true);
	~ModuleImguiWindow();

	bool Start();
	//IMGUI_API bool          ShowWindow(bool* p_open = NULL);
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();
	void Histogram();
	void GeneratePrimitives();
	void Inspector();

	//bools
	bool ActiveDemoWindows = true;
	bool openConsole = true;

	bool AboutTxt = false;
	bool FullScreenEnable = false;
	SDL_bool Resizable = SDL_FALSE;
	SDL_bool Borderless = SDL_FALSE;
	bool ActiveResizable = true;
	bool CloseApp = false;
	bool Wireframe = false;
	bool DepthTest = true;
	bool CullFace = true;
	bool Lighting = true;
	bool ColorMaterial = true;
	//const char fps_log[60];
	//const char ms_log[60];
	//float
	float BrightnessStart = 1.f;
	float BrightnessMin = 0.f;
	float BrightnessMax = 1.f;


	
	//ints
	int WidthMin = 0;
	int WidthMax = 2040;
	int CurrentFrame;
	int CurrentMilisecond;
	int CubPicked = NULL;
	int PiramidPicked = NULL;
	
private:



	std::vector<float> FPS;
	std::vector<float> Miliseconds;
};

