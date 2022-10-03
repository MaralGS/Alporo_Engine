#include "Globals.h"
#include "Application.h"
#include "ModuleImGuiWindow.h"

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "imgui.h"
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
#endif


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


void ModuleImguiWindow::ShowWindow(bool* p_open)
{
    
    // Et mostra les opcions del Example (Example Menu)
    static bool show_app_main_menu_bar = true;
    static bool show_app_ImGui_Demo_menu_bar = false;
    static bool show_app_documents = false;
    static bool show_app_console = false;
    static bool show_app_log = false;
    static bool show_app_layout = false;
    static bool show_app_property_editor = false;
    static bool show_app_long_text = false;
    static bool show_app_auto_resize = false;
    static bool show_app_constrained_resize = false;
    static bool show_app_simple_overlay = false;
    static bool show_app_fullscreen = false;
    static bool show_app_window_titles = false;
    static bool show_app_custom_rendering = false;

    /*if (show_app_main_menu_bar)       ShowExampleAppMainMenuBar();
    if (show_app_documents)           ShowExampleAppDocuments(&show_app_documents);
    if (show_app_console)             ShowExampleAppConsole(&show_app_console);
    if (show_app_log)                 ShowExampleAppLog(&show_app_log);
    if (show_app_layout)              ShowExampleAppLayout(&show_app_layout);
    if (show_app_property_editor)     ShowExampleAppPropertyEditor(&show_app_property_editor);
    if (show_app_long_text)           ShowExampleAppLongText(&show_app_long_text);
    if (show_app_auto_resize)         ShowExampleAppAutoResize(&show_app_auto_resize);
    if (show_app_constrained_resize)  ShowExampleAppConstrainedResize(&show_app_constrained_resize);
    if (show_app_simple_overlay)      ShowExampleAppSimpleOverlay(&show_app_simple_overlay);
    if (show_app_fullscreen)          ShowExampleAppFullscreen(&show_app_fullscreen);
    if (show_app_window_titles)       ShowExampleAppWindowTitles(&show_app_window_titles);
    if (show_app_custom_rendering)    ShowExampleAppCustomRendering(&show_app_custom_rendering);*/

    // Dear ImGui Tools/Apps (accessible from the "Tools" menu)
    static bool show_app_metrics = false;
    static bool show_app_debug_log = false;
    static bool show_app_stack_tool = false;
    static bool show_app_about = false;
    static bool show_app_style_editor = false;

    if (show_app_metrics)
        ImGui::ShowMetricsWindow(&show_app_metrics);
    if (show_app_debug_log)
        ImGui::ShowDebugLogWindow(&show_app_debug_log);
    if (show_app_stack_tool)
        ImGui::ShowStackToolWindow(&show_app_stack_tool);
    if (show_app_about)
        ImGui::ShowAboutWindow(&show_app_about);
    if (show_app_style_editor)
    {
        ImGui::Begin("Dear ImGui Style Editor", &show_app_style_editor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    // Demonstrate the various window flags. Typically you would just use the default!
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

    // Main body of the Demo window starts here.
    if (!ImGui::Begin("ImGui Menu", p_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

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
            //IMGUI_DEMO_MARKER("Menu/File");
            
            ImGui::ShowExitMenu();
            ImGui::EndMenu();
        }


      /*  if (ImGui::BeginMenu("Menu"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ImGui::ShowDemoWindow();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Examples"))
        {
            //IMGUI_DEMO_MARKER("Menu/Examples");
            if (ImGui::MenuItem("Show ImGui Demo Menu", NULL, &show_app_ImGui_Demo_menu_bar))
            {
                //ActiveDemo = true;
            }
            ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
            ImGui::MenuItem("Console", NULL, &show_app_console);
            ImGui::MenuItem("Log", NULL, &show_app_log);
            ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
            ImGui::MenuItem("Property editor", NULL, &show_app_property_editor);
            ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
            ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
            ImGui::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
            ImGui::MenuItem("Simple overlay", NULL, &show_app_simple_overlay);
            ImGui::MenuItem("Fullscreen window", NULL, &show_app_fullscreen);
            ImGui::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
            ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
            ImGui::MenuItem("Documents", NULL, &show_app_documents);
            ImGui::EndMenu();
        }
        //if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
        if (ImGui::BeginMenu("Tools"))
        {
           // IMGUI_DEMO_MARKER("Menu/Tools");
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
            const bool has_debug_tools = true;
#else
            const bool has_debug_tools = false;
#endif
            ImGui::MenuItem("Metrics/Debugger", NULL, &show_app_metrics, has_debug_tools);
            ImGui::MenuItem("Debug Log", NULL, &show_app_debug_log, has_debug_tools);
            ImGui::MenuItem("Stack Tool", NULL, &show_app_stack_tool, has_debug_tools);
            ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
            ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
            ImGui::EndMenu();
        }*/
        ImGui::EndMenuBar();
    }

    ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Spacing();

    //Confiration options
    if (ImGui::CollapsingHeader("Configuration"))
    {
        ImGuiIO& io = ImGui::GetIO();

        if (ImGui::TreeNode("Configuration##2"))
        {
            ImGui::CheckboxFlags("io.ConfigFlags: NavEnableKeyboard", &io.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard);
            ImGui::SameLine(); //HelpMarker("Enable keyboard controls.");
            ImGui::CheckboxFlags("io.ConfigFlags: NavEnableGamepad", &io.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
            ImGui::SameLine(); //HelpMarker("Enable gamepad controls. Require backend to set io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details.");
            ImGui::CheckboxFlags("io.ConfigFlags: NavEnableSetMousePos", &io.ConfigFlags, ImGuiConfigFlags_NavEnableSetMousePos);
            ImGui::SameLine(); //HelpMarker("Instruct navigation to move the mouse cursor. See comment for ImGuiConfigFlags_NavEnableSetMousePos.");
            ImGui::CheckboxFlags("io.ConfigFlags: NoMouse", &io.ConfigFlags, ImGuiConfigFlags_NoMouse);
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)
            {
                // The "NoMouse" option can get us stuck with a disabled mouse! Let's provide an alternative way to fix it:
                if (fmodf((float)ImGui::GetTime(), 0.40f) < 0.20f)
                {
                    ImGui::SameLine();
                    ImGui::Text("<<PRESS SPACE TO DISABLE>>");
                }
                if (ImGui::IsKeyPressed(ImGuiKey_Space))
                    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }
            ImGui::CheckboxFlags("io.ConfigFlags: NoMouseCursorChange", &io.ConfigFlags, ImGuiConfigFlags_NoMouseCursorChange);
            ImGui::SameLine(); //HelpMarker("Instruct backend to not alter mouse cursor shape and visibility.");
            ImGui::Checkbox("io.ConfigInputTrickleEventQueue", &io.ConfigInputTrickleEventQueue);
            ImGui::SameLine(); //HelpMarker("Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.");
            ImGui::Checkbox("io.ConfigInputTextCursorBlink", &io.ConfigInputTextCursorBlink);
            ImGui::SameLine();// HelpMarker("Enable blinking cursor (optional as some users consider it to be distracting).");
            ImGui::Checkbox("io.ConfigInputTextEnterKeepActive", &io.ConfigInputTextEnterKeepActive);
            ImGui::SameLine();// HelpMarker("Pressing Enter will keep item active and select contents (single-line only).");
            ImGui::Checkbox("io.ConfigDragClickToInputText", &io.ConfigDragClickToInputText);
            ImGui::SameLine(); //HelpMarker("Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving).");
            ImGui::Checkbox("io.ConfigWindowsResizeFromEdges", &io.ConfigWindowsResizeFromEdges);
            ImGui::SameLine(); //HelpMarker("Enable resizing of windows from their edges and from the lower-left corner.\nThis requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback.");
            ImGui::Checkbox("io.ConfigWindowsMoveFromTitleBarOnly", &io.ConfigWindowsMoveFromTitleBarOnly);
            ImGui::Checkbox("io.MouseDrawCursor", &io.MouseDrawCursor);
            ImGui::SameLine();// HelpMarker("Instruct Dear ImGui to render a mouse cursor itself. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");
            ImGui::Text("Also see Style->Rendering for rendering options.");
            ImGui::TreePop();
            ImGui::Separator();
        }

        //  IMGUI_DEMO_MARKER("Configuration/Backend Flags");
        if (ImGui::TreeNode("Backend Flags"))
        {
            
           /* HelpMarker(
                "Those flags are set by the backends (imgui_impl_xxx files) to specify their capabilities.\n"
                "Here we expose them as read-only fields to avoid breaking interactions with your backend.");*/

            // Make a local copy to avoid modifying actual backend flags.
            // FIXME: We don't use BeginDisabled() to keep label bright, maybe we need a BeginReadonly() equivalent..
            ImGuiBackendFlags backend_flags = io.BackendFlags;
            ImGui::CheckboxFlags("io.BackendFlags: HasGamepad", &backend_flags, ImGuiBackendFlags_HasGamepad);
            ImGui::CheckboxFlags("io.BackendFlags: HasMouseCursors", &backend_flags, ImGuiBackendFlags_HasMouseCursors);
            ImGui::CheckboxFlags("io.BackendFlags: HasSetMousePos", &backend_flags, ImGuiBackendFlags_HasSetMousePos);
            ImGui::CheckboxFlags("io.BackendFlags: RendererHasVtxOffset", &backend_flags, ImGuiBackendFlags_RendererHasVtxOffset);
            ImGui::TreePop();
            ImGui::Separator();
        }

        // IMGUI_DEMO_MARKER("Configuration/Style");
        if (ImGui::TreeNode("Style"))
        {
            //  HelpMarker("The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
            ImGui::ShowStyleEditor();
            ImGui::TreePop();
            ImGui::Separator();
        }

        //IMGUI_DEMO_MARKER("Configuration/Capture, Logging");
        if (ImGui::TreeNode("Capture/Logging"))
        {
          /*  HelpMarker(
                "The logging API redirects all text output so you can easily capture the content of "
                "a window or a block. Tree nodes can be automatically expanded.\n"
                "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");*/
            ImGui::LogButtons();

            // HelpMarker("You can also call ImGui::LogText() to output directly to the log without a visual output.");
            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::TreePop();
        }
    }
    //Hardware Applcation
    if (ImGui::CollapsingHeader("Application"))
    {
        /*char title[25];
        //fps
        sprintf_s(title, 25, "Framrate %.1f", fps_log[fps_log.size() - 1]);
        ImGui::PlotHistogram("##framrate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
        //miliseconds
        sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size()-1]);
        ImGui::PlotHistogram("##framrate", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));*/
    }
   //Windows Options
    if (ImGui::CollapsingHeader("Window options"))
    {
        //Windows options
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
       ImGui::BulletText("Refresh rate: %d");
       if (ImGui::Checkbox("Active Fullscreen", &FullScreenEnable))
       {

       }
       ImGui::SameLine();
       if (ImGui::Checkbox("Resizable", &FullScreenEnable))
       {

       }
            //2n line
       if (ImGui::Checkbox("Borderless", &FullScreenEnable))
       {

       }
       ImGui::SameLine();
       if (ImGui::Checkbox("Full Desktop", &FullScreenEnable))


       {

       }
    }

    //Hardware Detection
    if (ImGui::CollapsingHeader("Hardware"))
    {
        if (ImGui::Checkbox("Active", &Dummy))
        {
            
        }
        ImGui::BulletText("CPUs: ");
        ImGui::SameLine(); 
       // ImGui::TextColored(CPU); ;
    }


    ImGui::PopItemWidth();
    ImGui::End();
}


bool ModuleImguiWindow::PostUpdate()
{
    bool ret = true;
    if (CloseApp == true) ret = false;

	return ret;
}

bool ModuleImguiWindow::CleanUp()
{
	LOG("Cleaning Module");

	return true;
}

static void ImGui::ShowExitMenu()
{
    ImGui::MenuItem("Exit Menu", NULL, false, false);
    if (ImGui::MenuItem("Close Aplication")){
       // SDL_DestroyWindow(window);
    }
    if (ImGui::MenuItem("Cancel")) {}
   
    /*
   IMGUI_DEMO_MARKER("Examples/Menu");
   ImGui::MenuItem("(demo menu)", NULL, false, false);
   if (ImGui::MenuItem("New")) {}
   if (ImGui::MenuItem("Open", "Ctrl+O")) {}
   if (ImGui::BeginMenu("Open Recent"))
   {
       ImGui::MenuItem("fish_hat.c");
       ImGui::MenuItem("fish_hat.inl");
       ImGui::MenuItem("fish_hat.h");
       if (ImGui::BeginMenu("More.."))
       {
           ImGui::MenuItem("Hello");
           ImGui::MenuItem("Sailor");
           if (ImGui::BeginMenu("Recurse.."))
           {
               ShowExampleMenuFile();
               ImGui::EndMenu();
           }
           ImGui::EndMenu();
       }
       ImGui::EndMenu();
   }
   if (ImGui::MenuItem("Save", "Ctrl+S")) {}
   if (ImGui::MenuItem("Save As..")) {}

   ImGui::Separator();
   IMGUI_DEMO_MARKER("Examples/Menu/Options");
   if (ImGui::BeginMenu("Options"))
   {
       static bool enabled = true;
       ImGui::MenuItem("Enabled", "", &enabled);
       ImGui::BeginChild("child", ImVec2(0, 60), true);
       for (int i = 0; i < 10; i++)
           ImGui::Text("Scrolling Text %d", i);
       ImGui::EndChild();
       static float f = 0.5f;
       static int n = 0;
       ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
       ImGui::InputFloat("Input", &f, 0.1f);
       ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
       ImGui::EndMenu();
   }

   IMGUI_DEMO_MARKER("Examples/Menu/Colors");
   if (ImGui::BeginMenu("Colors"))
   {
       float sz = ImGui::GetTextLineHeight();
       for (int i = 0; i < ImGuiCol_COUNT; i++)
       {
           const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
           ImVec2 p = ImGui::GetCursorScreenPos();
           ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
           ImGui::Dummy(ImVec2(sz, sz));
           ImGui::SameLine();
           ImGui::MenuItem(name);
       }
       ImGui::EndMenu();
   }

   // Here we demonstrate appending again to the "Options" menu (which we already created above)
   // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
   // In a real code-base using it would make senses to use this feature from very different code locations.
   if (ImGui::BeginMenu("Options")) // <-- Append!
   {
       IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
       static bool b = true;
       ImGui::Checkbox("SomeOption", &b);
       ImGui::EndMenu();
   }

   if (ImGui::BeginMenu("Disabled", false)) // Disabled
   {
       IM_ASSERT(0);
   }
   if (ImGui::MenuItem("Checked", NULL, true)) {}
   if (ImGui::MenuItem("Quit", "Alt+F4")) {}*/
}