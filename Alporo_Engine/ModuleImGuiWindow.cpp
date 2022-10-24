#include "Globals.h"
#include "Application.h"
#include "ModuleImGuiWindow.h"
#include "HMenuWindows.h"
#include "imgui.h"
#include<vector>
/*#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef IMGUI_DISABLE

// System includes
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127)     // condition expression is constant
#pragma warning (disable: 4996)     // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#pragma warning (disable: 26451)    // [Static Analyzer] Arithmetic overflow : Using operator 'xxx' on a 4 byte value and then casting the result to an 8 byte value. Cast the value to the wider type before calling operator 'xxx' to avoid overflow(io.2).
#endif

// Clang/GCC warnings with -Weverything
#if defined(__clang__)
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option"         // warning: unknown warning group 'xxx'                     // not all warnings are known by all Clang versions and they tend to be rename-happy.. so ignoring warnings triggers new warnings on some configuration. Great!
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"                // warning: unknown warning group 'xxx'
#pragma clang diagnostic ignored "-Wold-style-cast"                 // warning: use of old-style cast                           // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"        // warning: 'xx' is deprecated: The POSIX name for this..   // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"       // warning: cast to 'void *' from smaller integer type
#pragma clang diagnostic ignored "-Wformat-security"                // warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"          // warning: declaration requires an exit-time destructor    // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wunused-macros"                  // warning: macro is not used                               // we define snprintf/vsnprintf on Windows so they are available, but not always used.
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning: zero as null pointer constant                   // some standard header variations use #define NULL 0
#pragma clang diagnostic ignored "-Wdouble-promotion"               // warning: implicit conversion from 'float' to 'double' when passing argument to function  // using printf() is a misery with this as C++ va_arg ellipsis changes float to double.
#pragma clang diagnostic ignored "-Wreserved-id-macro"              // warning: macro name is a reserved identifier
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"  // warning: implicit conversion from 'xxx' to 'float' may lose precision
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"                  // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"      // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"          // warning: format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"         // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"               // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wmisleading-indentation"   // [__GNUC__ >= 6] warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#endif

// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

// Helpers
#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif

// Format specifiers, printing 64-bit hasn't been decently standardized...
// In a real application you should be using PRId64 and PRIu64 from <inttypes.h> (non-windows) and on Windows define them yourself.
#ifdef _MSC_VER
#define IM_PRId64   "I64d"
#define IM_PRIu64   "I64u"
#else
#define IM_PRId64   "lld"
#define IM_PRIu64   "llu"
#endif
#endif*/

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

bool ModuleImguiWindow::PreUpdate() {

	return true;
}

update_status ModuleImguiWindow::Update(float dt)
{
    update_status ret = UPDATE_CONTINUE;


    return ret;
}

// -----------------------------------------------------------------


bool ModuleImguiWindow::ShowWindow(bool* p_open)
{
  // Main body of the Demo window starts here.
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool unsaved_document = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    ImGui::Begin("ImGui Menu", p_open, window_flags);
  
    // Most "big" widgets share a common width settings by default. See 'Demo->Layout->Widgets Width' for details.
    // e.g. Use 2/3 of the space for widgets and 1/3 for labels (right align)
    //ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.35f);
    // e.g. Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    // Menu Bar
    if (ImGui::BeginMenuBar())
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
           if(ImGui::MenuItem("Close Aplication")) {

               return false;
            }
            if (ImGui::MenuItem("Cancel")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Spacing();

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
        FPSStart = App->prevLastSecFrameCount;
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


    ImGui::PopItemWidth();
    ImGui::End();


    HMenu HM;
    HM.PrintMenu();

    return true;
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
    ImGui::BulletText("FPS: ");
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
        ImGui::BulletText("Miliseconds: ");
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
