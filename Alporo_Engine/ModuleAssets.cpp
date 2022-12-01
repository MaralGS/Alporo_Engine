#include "Globals.h"
#include "Application.h"
#include "ModuleAssets.h"


ModuleAssets::ModuleAssets(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAssets::~ModuleAssets()
{}


bool ModuleAssets::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleAssets::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status ModuleAssets::Update(float dt)
{

	ImGui::Begin("AssetsWindow");
	{

	}
	ImGui::End();


	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleAssets::CleanUp()
{
	LOG(LogType::ERRORS, "Unloading Intro Assets");

	return true;
}
