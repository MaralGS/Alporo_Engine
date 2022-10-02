#include "Globals.h"
#include "Application.h"
#include "ModuleImGuiWindow.h"

ModuleImguiWindow::ModuleImguiWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleImguiWindow::~ModuleImguiWindow()
{

}

// -----------------------------------------------------------------
bool ModuleImguiWindow::Start()
{
	LOG("Started ImGuiWindow");
	bool ret = true;

	return ret;
}

update_status ModuleImguiWindow::PreUpdate(float dt) {

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleImguiWindow::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

update_status ModuleImguiWindow::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleImguiWindow::CleanUp()
{
	LOG("Cleaning Module");

	return true;
}

