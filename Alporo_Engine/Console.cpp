#include "Console.h"
#include "imgui.h"
#include "Globals.h"
#include "ModuleImGuiWindow.h"

vector<DebugLogs> Logs::logs;
vector<DebugLogs> Logs::logsCopy;

int Logs::countDebug = 0;
int Logs::countSyst = 0;
int Logs::countWarn = 0;

bool Logs::showPath = false;

bool Logs::warnignDebug = true;
bool Logs::systemDebug = true;
bool Logs::msgDebug = true;

float Logs::colorEdit[3] = { 0.4f, 0.7f, 0.0f };

void Logs::PrintDebug()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Separator();

		if (ImGui::Button("Clear"))
		{
			logs.clear();
			logsCopy.clear();
			countDebug = 0;
			countSyst = 0;
			countWarn = 0;
		}

		ImGui::EndMenuBar();
	}

	for (size_t i = 0; i < logs.size(); i++)
	{
		DebugLogs l = logs[i];
		string s = "";


		if (msgDebug && l.type == LogType::LOGS)
		{
		
			ImGui::Text("LOG |");
			ImGui::SameLine();
			ImGui::Text(l.file.c_str());
			ImGui::SameLine();
			ImGui::Text(l.st.c_str());
			
		}
		else if (systemDebug && logs[i].type == LogType::ERRORS)
		{
		
			ImGui::Text("ERROR |");
			ImGui::SameLine();
			ImGui::Text(l.file.c_str());
			ImGui::SameLine();
			ImGui::Text(l.st.c_str());
		}
		else if (warnignDebug && logs[i].type == LogType::WARNING)
		{
	
			ImGui::Text("WARNING |");
			ImGui::SameLine();
			ImGui::Text(l.file.c_str());
			ImGui::SameLine();
			ImGui::Text(l.st.c_str());
		}
	}

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 20)
	{
		ImGui::SetScrollY(ImGui::GetScrollMaxY());
	}

	//ImGui::PopStyleColor(1);
	//ImGui::PopStyleColor(1);
	ImGui::End();
}





void Logs::UnCollapseDebug()
{
	logs.clear();
	logs = logsCopy;
	logsCopy.clear();
}


