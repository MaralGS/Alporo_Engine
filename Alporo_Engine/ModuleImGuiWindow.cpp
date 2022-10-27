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
	LOG(LogType::LOGS, "Started ImGuiWindow");
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
            if (ImGui::RadioButton(" Console  ", openConsole))
            {
                openConsole = !openConsole;
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
            GeneratePrimitives();

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
                   SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
               }

               else
               {
                   SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_MAXIMIZED);
               }
               
               
           }
           //RESIZABLE WINDOWS (Si la pots escalar o no amb el cursor)
           if (ImGui::Checkbox("Resizable Windows", &ActiveResizable));
           if (ActiveResizable == true)
           {
               Resizable = SDL_TRUE;
           }
           if (ActiveResizable == false)
           {
               Resizable = SDL_FALSE;
           }
          // SDL_SetWindowResizable(App->window->window, Resizable);
           SDL_SetWindowBordered(App->window->window, Borderless);

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
    if (ImGui::Begin("Inspector")) {
        Inspector();
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
	LOG(LogType::LOGS, "Cleaning Module");

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

void ModuleImguiWindow::GeneratePrimitives()
{
    if (ImGui::BeginMenu("Cube"))
    {
        if (ImGui::Button("Generate Cube")) {
            Quad* Q = new Quad();
            App->OpenGLPrimitives->Cub.push_back(Q);
            App->OpenGLPrimitives->NumQuads++;
        }
        if (ImGui::Button("Delete Cube")) {
            if (App->OpenGLPrimitives->NumQuads >= 1)
            {
                if (App->OpenGLPrimitives->Cub.size() == App->OpenGLPrimitives->NumQuads)
                {
                    if (CubPicked != App->OpenGLPrimitives->NumQuads)
                    {
                        for (int i = CubPicked; i < App->OpenGLPrimitives->NumQuads - 1; i++)
                        {
                            App->OpenGLPrimitives->Cub[i] = App->OpenGLPrimitives->Cub[i + 1];

                        }
                    }

                    App->OpenGLPrimitives->Cub.pop_back();
                    App->OpenGLPrimitives->NumQuads--;
                    if (CubPicked != 0)
                    {
                        CubPicked--;
                    }
                }
            }
        }
        ImGui::EndMenu();
    }

    //generate and delete a Piramide
    if (ImGui::BeginMenu("Piramide"))
    {
        if (ImGui::Button("Generate Piramid")) {
            Triangle* Q = new Triangle();
            App->OpenGLPrimitives->Piramid.push_back(Q);
            App->OpenGLPrimitives->NumPiramid++;
        }
        if (ImGui::Button("Delete Piramid")) {
            if (App->OpenGLPrimitives->NumPiramid >= 1)
            {
                if (App->OpenGLPrimitives->Piramid.size() == App->OpenGLPrimitives->NumPiramid)
                {
                    if (PiramidPicked != App->OpenGLPrimitives->NumPiramid)
                    {
                        for (int i = PiramidPicked; i < App->OpenGLPrimitives->NumPiramid - 1; i++)
                        {
                            App->OpenGLPrimitives->Piramid[i] = App->OpenGLPrimitives->Piramid[i + 1];

                        }
                    }

                    App->OpenGLPrimitives->Piramid.pop_back();
                    App->OpenGLPrimitives->NumPiramid--;
                    if (PiramidPicked != 0)
                    {
                        PiramidPicked--;
                    }
                }
            }

        }

        if (ImGui::Checkbox("Draw Cilindre", &App->OpenGLPrimitives->CilindreStats.DrawCilindre));

        ImGui::EndMenu();
    }
}

void ModuleImguiWindow::Inspector()
{
    for (int i = 0; i < App->OpenGLPrimitives->NumQuads; i++)
    {
        char Name[32];
        sprintf(Name, "Cube %d", i + 1);

        if (ImGui::Selectable(Name, i == CubPicked, 0)) {
            CubPicked = i;
            PiramidPicked = NULL;
            App->OpenGLPrimitives->PM = 1;

        }
        if (i == CubPicked)
        {
            ImGui::BulletText("Cube %d:", i + 1);
            ImGui::BulletText("X: %.2f\nY: %.2f\nZ: %.2f", App->OpenGLPrimitives->Cub[i]->Pos2.x, App->OpenGLPrimitives->Cub[i]->Pos2.y, App->OpenGLPrimitives->Cub[i]->Pos2.z);
            ImGui::Separator();
        }

    }

    for (int i = 0; i < App->OpenGLPrimitives->NumPiramid; i++)
    {
        char Name[32];
        sprintf(Name, "Piramid %d", i + 1);

        if (ImGui::Selectable(Name, i == PiramidPicked, 0)) {
            PiramidPicked = i;
            CubPicked = NULL;
            App->OpenGLPrimitives->PM = 2;
        }
        if (i == PiramidPicked)
        {
            ImGui::BulletText("Piramid  %d:", i + 1);
            ImGui::BulletText("X: %.2f\nY: %.2f\nZ: %.2f", App->OpenGLPrimitives->Piramid[i]->Pos2.x, App->OpenGLPrimitives->Piramid[i]->Pos2.y, App->OpenGLPrimitives->Piramid[i]->Pos2.z);
            ImGui::Separator();
        }
    }
}
