#include "Globals.h"
#include "Application.h"
#include "ModuleImGuiWindow.h"
#include "Mesh.h"
#include "imgui.h"
#include "IL.h"

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
    RootGO = new GameObject();


	LOG(LogType::LOGS, "Started ImGuiWindow");
	bool ret = true;

	return ret;
}

update_status ModuleImguiWindow::PreUpdate(float dt) {


	return UPDATE_CONTINUE;
}

update_status ModuleImguiWindow::Update(float dt)
{
    ImGuiWindowFlags window_flags = 2;
   
   window_flags |= ImGuiWindowFlags_NoMove;
   window_flags |= ImGuiWindowFlags_NoResize;

   // ImGui::ShowDemoWindow();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Gui Demo"))
            {
                ActiveDemoWindows = !ActiveDemoWindows;
            }
            if (ImGui::MenuItem("Console "))
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

            if (ImGui::RadioButton("About", AboutTxt))
            {
                AboutTxt = !AboutTxt;
            }
            if (AboutTxt == true)
            {
                if (ImGui::Begin("About", false, window_flags))
                {

                    ImGui::Text("Alporo_Engine vA 0.1\n\nBy Pol Maresch & Alex Garcia");

                    ImGui::Text("3rd Party Libraries Used:");
                    ImGui::BulletText("SDL: Version 2.0.4");
                    ImGui::BulletText("ImGui: Version 1.84 WIP");
                    ImGui::BulletText("OpenGl: Version 4.6.0");
                    ImGui::BulletText("DevIL: Version 180");
                    ImGui::BulletText("MathGeoLib: Version 1.15");
                    ImGui::BulletText("Glew: Version 7.0");

                    ImGui::Text("License: MIT LicenseMIT License");
                    ImGui::Text("Copyright(c) 2022 MaralGS");
                    ImGui::Text("Permission is hereby granted, free of charge,\nto anyperson obtaining a copy of this software and\nassociated documentation files(the 'Software'),\nto deal to use, copy, modify, merge, publish,\ndistribute, sublicense, and /or sell copies of the\nSoftware, and to permit persons to whom the Software\nis furnished to do so, subject to the following\nconditions:");
                    ImGui::Text("\n");
                    ImGui::Text("The above copyright notice and this permissio\nnotice shall be included in all copies or\nsubstantial portions of the Software.");
                    ImGui::Text("\n");
                    ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY\nOF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT\nLIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\nIN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS\nBE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\nWHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\nARISING FROM, OUT OF OR IN CONNECTION WITH THE\nSOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
                }
                ImGui::End();
                
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

        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        if (ImGui::CollapsingHeader("Hardware"))
        {
            ImGui::BulletText("Compiled SDL Version: %u.%u.%u", compiled.major, compiled.minor, compiled.patch);
            ImGui::BulletText("Linked SDL Version: %u.%u.%u", linked.major, linked.minor, linked.patch);
            ImGui::Separator();
            ImGui::BulletText("Imgui Version: %s\nImgui Version Num: %d", IMGUI_VERSION, IMGUI_VERSION_NUM);
            ImGui::Separator();
            ImGui::BulletText("OPGL Version:\n%s", glGetString(GL_VERSION));
            ImGui::Separator();
            ImGui::BulletText("DevIL Version: %d", IL_VERSION);
            ImGui::Separator();
            ImGui::BulletText("CPUs: %d (Cache %dKb)", SDL_GetCPUCount(),SDL_GetCPUCacheLineSize());
            ImGui::BulletText("System RAM: %dGb", SDL_GetSystemRAM()/1000);
        }

    }
    ImGui::End();

    //GameObjects hieracy
    if (ImGui::Begin("GameObjects")) {
        hieraci(RootGO);
    }
    ImGui::End();

    if (!App->input->GetMouseButton(SDL_BUTTON_LEFT))
    {
        CreatedOnce = true;
    }

    if (Selected != nullptr)
    {
        Selected->CreateInspector();
    }
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
   int primitive;

    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::Button("Generate Empty GameObject")) {
            primitive = 1;
            App->LoadFbx->PrimitivesObjects(primitive);
        }

        if (ImGui::Button("Generate Cube")) {
            primitive = 2;
            App->LoadFbx->PrimitivesObjects(primitive);
        }

        if (ImGui::Button("Generate Plane")) {
            primitive = 3;
            App->LoadFbx->PrimitivesObjects(primitive);
        }

        if (ImGui::Button("Generate Pyramid")) {
            primitive = 4;
            App->LoadFbx->PrimitivesObjects(primitive);
        }

        if (ImGui::Button("Generate Sphere")) {
            primitive = 5;
            App->LoadFbx->PrimitivesObjects(primitive);
        }
        if (ImGui::Button("Generate Cylinder")) {        
            primitive = 6;
            App->LoadFbx->PrimitivesObjects(primitive);
        }

        if (ImGui::Button("Delete GameObject")) {
            Selected->~GameObject();
        }

        ImGui::EndMenu();
    }
   // if (ImGui::Checkbox("Draw Cilindre", &App->OpenGLPrimitives->CilindreStats.DrawCilindre));
    if (ImGui::Checkbox("Draw 1rst FBX", &App->LoadFbx->FBX1));
    if (ImGui::Checkbox("Draw 2rst FBX", &App->LoadFbx->FBX2));
    if (ImGui::Checkbox("Draw 3rst FBX", &App->LoadFbx->FBX3));

}

void ModuleImguiWindow::hieraci(GameObject* parent)
{
    ImGuiTreeNodeFlags treeF = ImGuiTreeNodeFlags_DefaultOpen;


    if (parent->child.size() == 0) {
        treeF |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }

    if (parent == Selected)
    {
        treeF |= ImGuiTreeNodeFlags_Selected;
    }
    bool openTree = ImGui::TreeNodeEx(parent, treeF, parent->name.c_str());


    if (openTree)
    {
        if (!parent->child.empty())
        {
            for (int i = 0; i < parent->child.size(); i++)
            {
                hieraci(parent->child[i]);
            }
            ImGui::TreePop();
        }

        else
        {
            treeF |= ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
        }

    }

    if (parent != RootGO)
    {
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("GameObject", parent, sizeof(GameObject*));

            Selected = parent;

           ImGui::Text("Moving Object");
           ImGui::EndDragDropSource();
       }
       if (ImGui::IsItemHovered() && App->input->GetMouseButton(SDL_BUTTON_LEFT) && CreatedOnce == true)
       {
           CreatedOnce = false;
           Selected = parent;
       }

   }

    if (ImGui::BeginDragDropTarget() && Selected != nullptr)
    {
        int SGo;
        if (ImGui::AcceptDragDropPayload("GameObject"))
        {
            for (int i = 0; i < Selected->Parent->child.size(); i++) {
                if (Selected == Selected->Parent->child[i]) {
                    SGo = i;
                }
            }

            parent->child.push_back(Selected);

            for (int i = SGo; i < Selected->Parent->child.size() - 1; i++)
            {

                Selected->Parent->child[i] = Selected->Parent->child[i + 1];

            }
            Selected->Parent = parent;

            parent->Parent->child.pop_back();

        
            Selected = nullptr;
        }
        ImGui::EndDragDropTarget();
    }

    if (App->input->GetMouseButton(SDL_BUTTON_RIGHT))
    {
        Selected = nullptr;
    }

}

