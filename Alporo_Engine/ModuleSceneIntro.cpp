#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "CameraObject.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	//Root = CreateGObject("root", nullptr);

	LOG(LogType::LOGS,"Loading Intro assets");
	bool ret = true;

	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG(LogType::ERRORS,"Unloading Intro scene");

	return true;
}


// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Grid p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	if (play == true)
	{
		timer += dt;
	}
	if (stop == true)
	{
		timer = 0;
	}

	if (ImGui::Begin("Game", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar)) {
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("STOP")) {
				ImGui::SetWindowFocus("GameWindow");
				stop = true;
				play = false;
			}
			ImGui::Separator();
			if (ImGui::Button("PAUSE")) {
				play = false;
			}
			ImGui::Separator();
			ImGui::Text("%.00f", timer);
			ImGui::EndMenuBar();
		}
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("GameRender");
		// Get the size of the child (i.e. the whole draw size of the windows).
		ImVec2 wsize = ImGui::GetWindowSize();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.

		ImGui::Image((ImTextureID)App->camera->Ccamera->bufferCam, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}
	ImGui::End();

	ImGui::Begin("GameWindow", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::Button("PLAY")) {
			ImGui::SetWindowFocus("Game");	
			App->imguiwindows->Selected = App->camera->GameCamera;
			play = true;
			pause = false;
			stop = false;
		}
		ImGui::Separator();
		if (ImGui::Button("STOP")) {
			ImGui::SetWindowFocus("GameWindow");
			stop = true;
			play = false;
		}
		ImGui::Separator();
		if (ImGui::Button("PAUSE")) {
			play = false;
		}
		ImGui::Separator();
		ImGui::Text("%.00f", timer);
		ImGui::EndMenuBar();
	}
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("GameRender");
		// Get the size of the child (i.e. the whole draw size of the windows).
		ImVec2 wsize = ImGui::GetWindowSize();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)App->camera->Mcamera->bufferCam, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
		ImGui::End();

	
	return UPDATE_CONTINUE;
}

