#include "HMenuWindows.h"
#include "imgui.h"
#include "SDL.h"


void HMenu::PrintMenu()
{
	ImGui::Begin("Menus", false, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar); //| ImGuiWindowFlags_NoDocking 

	ImGui::TextColored({0,255,0,255}, "HOLA");
	/*if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::Button("GitHub", ImVec2(60, 20)))
				ShellExecute(0, 0, "https://github.com/bielrabasa/TheSeed_GameEngine", 0, 0, SW_SHOW);

			if (ImGui::Button("Exit", ImVec2(60, 20)))
				quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::Button("Circles", ImVec2(60, 20)))
			{
			}

			if (ImGui::Button("Cube", ImVec2(60, 20)))
			{
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}*/

	ImGui::End();
}