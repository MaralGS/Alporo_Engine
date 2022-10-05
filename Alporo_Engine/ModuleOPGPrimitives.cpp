#include "Globals.h"
#include "Application.h"
#include "ModuleOPGPrimitives.h"

ModuleOPGPrimitives::ModuleOPGPrimitives(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleOPGPrimitives::~ModuleOPGPrimitives()
{

}


bool ModuleOPGPrimitives::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

bool ModuleOPGPrimitives::PreUpdate() {


	return true;
}

update_status ModuleOPGPrimitives::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleOPGPrimitives::PostUpdate() {


	return true;
}

bool ModuleOPGPrimitives::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}