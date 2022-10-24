#include "Globals.h"
#include "Application.h"
#include "ModuleImGuiWindow.h"
#include "imgui.h"
#include<vector>


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

update_status ModuleImguiWindow::Update(float dt)
{
   // ImGui::ShowDemoWindow();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Gui Demo"))
            {
                ActiveDemoWindows = !ActiveDemoWindows;
            }

            if (ImGui::MenuItem("Documentation"))
            {
                SDL_OpenURL("https://github.com/MaralGS/Alporo_Engine/wiki");
            }

            if (ImGui::MenuItem("Download lastest"))
            {
                SDL_OpenURL("https://github.com/MaralGS/Alporo_Engine/releases");
            }

            if (ImGui::MenuItem("Report a bug"))
            {
                SDL_OpenURL("https://github.com/MaralGS/Alporo_Engine/issues");
            }

            if (ImGui::MenuItem("About"))
            {
                AboutTxt = !AboutTxt;
            }

            if (AboutTxt == true)
            {
                ImGui::BulletText("Alporo_Engine");
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Exit"))
        {
            if (ImGui::MenuItem("Close Aplication")) {

                return UPDATE_STOP;
            }
            if (ImGui::MenuItem("Cancel")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (ImGui::Begin("Options")) {
        //Configuration options
        if (ImGui::CollapsingHeader("Configuration"))
        {
            if (ImGui::Checkbox("Draw Cube", &App->OpenGLPrimitives->DrawQuadra));
            if (ImGui::Checkbox("Draw Piramide", &App->OpenGLPrimitives->DrawPiramide));
            if (ImGui::Checkbox("Draw Cilindre", &App->OpenGLPrimitives->CilindreStats.DrawCilindre));

            ImGui::Checkbox("WireFrame", &Wireframe);
            ImGui::Checkbox("Depth Test", &DepthTest);
            ImGui::Checkbox("Cull Face", &CullFace);
            ImGui::Checkbox("Lighting", &Lighting);
            ImGui::Checkbox("Color Material", &ColorMaterial);

        }
        //Hardware Application
        if (ImGui::CollapsingHeader("Application"))
        {

            ImGui::Button("Alporo Engine"); ImGui::SameLine(); ImGui::Text("App name");
            ImGui::Button("UPC CITM"); ImGui::SameLine(); ImGui::Text("Organization");
            /*if (ImGui::SliderInt("Max FPS", &FPSStart, FPSMin, FPSMax)) {
                //SDL_SetWindowBrightness(App->window->window, FPSStart);
            }*/
            Histogram();
        }
       //Windows Options
        if (ImGui::CollapsingHeader("Window options"))
        {
            //Windows options
           ImGui::BulletText("Icon: *default*");
           if (ImGui::SliderFloat("Brightness", &BrightnessStart, BrightnessMin, BrightnessMax)) {
               SDL_SetWindowBrightness(App->window->window, BrightnessStart);
            }
           if (ImGui::SliderInt("Width", &App->window->width, WidthMin, WidthMax)) {
               SDL_SetWindowSize(App->window->window, App->window->width, SCREEN_HEIGHT);
            }
           if (ImGui::SliderInt("Height", &App->window->height, WidthMin, WidthMax)) {
               SDL_SetWindowSize(App->window->window, SCREEN_WIDTH, App->window->height);
            }

           //refresh
          // ImGui::BulletText("Refresh rate: %d", SDL_GetNumVideoDisplays());
           if (ImGui::Checkbox("Active Fullscreen", &FullScreenEnable))
           {
               if (FullScreenEnable == true)
               {
                   SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);
               }

               else
               {
                   SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_MAXIMIZED);
               }
           }
        }

        //Hardware Detection
        if (ImGui::CollapsingHeader("Hardware"))
        {
            ImGui::BulletText("SDL Version: 2.0.4");
            ImGui::Separator();
            ImGui::BulletText("CPUs: %d (Cache %dKb)", SDL_GetCPUCount(),SDL_GetCPUCacheLineSize());
            ImGui::BulletText("System RAM: %dGb", SDL_GetSystemRAM()/1000);
            ImGui::Separator();
            //ImGui::BulletText("System RAM: %dGb", SDL_GetGPU()/1000);


           // ImGui::TextColored(CPU); ;
        }

    }

    ImGui::End();
    return UPDATE_CONTINUE;
}

update_status ModuleImguiWindow::PostUpdate()
{
    update_status ret = UPDATE_CONTINUE;

	return ret;
}

bool ModuleImguiWindow::CleanUp()
{
	LOG("Cleaning Module");

	return true;
}

void ModuleImguiWindow::Histogram()
{
    //FPS
    {
    CurrentFrame = App->prevLastSecFrameCount;
    ImGui::BulletText("FPS: %d", CurrentFrame);

    if (FPS.size() < 45)
    {
        FPS.push_back(App->prevLastSecFrameCount);
    }

    else if (FPS.size() == 45)
    {
        for (int i = 0; i <= 43; i++)
        {
            FPS[i] = FPS[i + 1];

        }
        FPS[44] = App->prevLastSecFrameCount;

        //FPS.pop_back();
    }

    SDL_GetPerformanceCounter();

    ImGui::PlotHistogram("##framrate", FPS.data(), FPS.size(), 0, NULL, 0.0f, 240, ImVec2(310, 100));
    }
    //miliseconds
   {
        CurrentMilisecond = (App->dt*1000);
        ImGui::BulletText("hrz Speed: %d ms", CurrentMilisecond);
        if (Miliseconds.size() < 45)
        {
            Miliseconds.push_back(App->dt * 1000);
        }

        else if (Miliseconds.size() == 45)
        {
            for (int i = 0; i <= 43; i++)
            {
                Miliseconds[i] = Miliseconds[i + 1];

            }
            Miliseconds[44] = App->dt*1000;
        }

        SDL_GetPerformanceCounter();

        ImGui::PlotHistogram("##Milisecods", Miliseconds.data(), Miliseconds.size(), 0, NULL, 0.f, 80.f, ImVec2(310, 100));
    }
}
