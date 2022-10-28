#include "Console.h"
#include "imgui.h"
#include "Globals.h"
#include "ModuleImGuiWindow.h"

vector<DebugConsole> Console::logs;
vector<DebugConsole> Console::logsCopy;



void Console::PrintDebug()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Separator();

		if (ImGui::Button("Clear"))
		{
			logs.clear();
			logsCopy.clear();
		}

		ImGui::EndMenuBar();
	}

	for (size_t i = 0; i < logs.size(); i++)
	{

		if (logs[i].type == LogType::LOGS)
		{
		
			ImGui::Text("LOG |");
			ImGui::SameLine();
			ImGui::Text(logs[i].file.c_str());
			ImGui::SameLine();
			ImGui::Text(logs[i].msg.c_str());
			
		}
		else if (logs[i].type == LogType::ERRORS)
		{
		
			ImGui::Text("ERROR |");
			ImGui::SameLine();
			ImGui::Text(logs[i].file.c_str());
			ImGui::SameLine();
			ImGui::Text(logs[i].msg.c_str());
		}
		else if (logs[i].type == LogType::WARNING)
		{
	
			ImGui::Text("WARNING |");
			ImGui::SameLine();
			ImGui::Text(logs[i].file.c_str());
			ImGui::SameLine();
			ImGui::Text(logs[i].msg.c_str());
		}
	}

	ImGui::End();
}


void Console::DebugConsole(string format, string file, LogType type)
{
	logs.push_back(struct DebugConsole(format, file, type));
}





