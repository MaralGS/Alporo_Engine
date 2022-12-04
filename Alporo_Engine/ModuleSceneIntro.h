#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "GameObject.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	ImVec2 WindowSize;
public:
	GameObject* Root = nullptr;
};
