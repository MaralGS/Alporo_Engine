#include "ModuleAssets.h"
#include "Application.h"

ModuleAssets::ModuleAssets(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleAssets::~ModuleAssets()
{
}

bool ModuleAssets::Init()
{
	return false;
}

bool ModuleAssets::Start()
{
	return false;
}

update_status ModuleAssets::PreUpdate(float dt)
{
	return update_status();
}

update_status ModuleAssets::Update(float dt)
{
	return update_status();
}

update_status ModuleAssets::PostUpdate()
{
	return update_status();
}

bool ModuleAssets::CleanUp()
{
	return false;
}
