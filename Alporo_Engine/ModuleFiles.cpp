#include "Application.h"
#include "ModuleFiles.h"
#include "ModuleImGuiWindow.h"
#include "PhysFS/include/physfs.h"

#include <cstdio>

ModuleFiles::ModuleFiles(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);

	SetCurrentPath("Assets");

	pathName = "";
	Reload = false;
}

ModuleFiles::~ModuleFiles()
{
	PHYSFS_deinit();
}

bool ModuleFiles::Init()
{

	return true;
}

bool ModuleFiles::Start()
{
	bool ret = true;

	GetDirectoryInfo(currentPath.c_str());

	return ret;
}

bool ModuleFiles::CleanUp()
{

	return true;
}

update_status ModuleFiles::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleFiles::Update(float dt)
{
	
		ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			PrintPathBar();
			ImGui::EndMenuBar();
		}

		PrintFiles();

		if (DeleteOption)
		{
			ImGui::Begin("FileMenu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

			if (ImGui::MenuItem("Delete"))
			{
				RemoveFile(FileInfo(fileName));
				Reload = true;
				DeleteOption = false;
				fileName = "";
			}
			ImGui::End();
		}

		if (App->input->GetKey(SDL_SCANCODE_DELETE) && ImGui::IsWindowHovered())
		{
			RemoveFile(FileInfo(fileName));
			fileName = "";
			Reload = true;
		}

		ImGui::End();


		if (Reload) {
			GetDirectoryInfo(currentPath.c_str());
			Reload = false;
		}

	return UPDATE_CONTINUE;
}

update_status ModuleFiles::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleFiles::PrintFiles()
{
	for (int i = 0; i < directionFiles.size(); i++)
	{
		FileInfo file = directionFiles[i];

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		if (file.path == fileName)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;


		if (pathName != file.path)
		{
			bool treepop = ImGui::TreeNodeEx((void*)(intptr_t)&file, treeNodeFlags, file.name.c_str());
			if (ImGui::IsItemHovered())
			{
				//Enter folder
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					DeleteOption = false;

					if (file.folder)
						SetCurrentPath(file.path.c_str());
				}
				//Select folder
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
				{
					DeleteOption = false;
					fileName = file.path;
				}
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
				{
					fileName = file.path;
					DeleteOption = true;
					ImGui::SetNextWindowPos(ImGui::GetMousePos());
				}
			}

			if (treepop)
			{
				ImGui::TreePop();
			}
		}
		else
		{
			char buffer[255];
			if (file.folder)
				strncpy(buffer, file.name.c_str(), sizeof(buffer) - 1);
			else
				strncpy(buffer, file.name.substr(0, file.name.find_last_of(".")).c_str(), sizeof(buffer) - 1);

		}

		ImGui::Separator();
	}

	if (ImGui::Button("Create Folder"))
	{
		PHYSFS_mkdir("Folder");
		Reload = true;
	}
	

}

void ModuleFiles::PrintPathBar()
{
	string auxpath = currentPath;

	while (auxpath.size() != 0)
	{
		int pos = auxpath.find_first_of("/");

		if (pos == -1) {
			ImGui::Text(auxpath.c_str());
			break;
		}

		if (ImGui::Button(auxpath.substr(0, pos).c_str()))
		{
			string end = auxpath.substr(0, auxpath.find_first_of("/"));

			SetCurrentPath(currentPath.substr(0, currentPath.find(end) + end.size()).c_str());
			break;
		}

		ImGui::Text("/");

		auxpath = auxpath.substr(pos + 1);
	}

}


void ModuleFiles::RemoveFile(FileInfo file)
{
	//File
	if (!file.folder) {
		PHYSFS_delete(file.name.c_str());
		return;
	}

	//Folder
	char** docs = PHYSFS_enumerateFiles(file.path.c_str());

	//Recursive deleting
	if (docs[0] != NULL) {
		for (int i = 0; docs[i] != NULL; i++) {
			string auxpath = file.path;
			FileInfo file(auxpath.append("/").append(docs[i]).c_str());
			PHYSFS_setWriteDir(file.path.c_str());
			RemoveFile(file);
		}
	}


	string writedir = file.path.substr(0, file.path.find_last_of("/"));
	PHYSFS_setWriteDir(writedir.c_str());
	PHYSFS_delete(file.name.c_str());
}

void ModuleFiles::GetDirectoryInfo(const char* dir)
{
	directionFiles.clear();

	char** docs = PHYSFS_enumerateFiles(dir);

	//Folders
	for (int i = 0; docs[i] != NULL; i++) {
		string direction = dir;
		direction.append("/").append(docs[i]);

		FileInfo file(direction);
		if (file.folder) directionFiles.push_back(file);
	}

	//Files
	for (int i = 0; docs[i] != NULL; i++) {
		string direction = dir;
		direction.append("/").append(docs[i]);
	
		FileInfo file(direction);
		if (!file.folder) directionFiles.push_back(file);
	}
}

void ModuleFiles::SetCurrentPath(const char* path)
{
	currentPath = path;
	PHYSFS_setWriteDir(path);
	GetDirectoryInfo(path);
}

FileInfo::FileInfo(string path)
{
	this->path = path;
	this->name = path.substr(path.find_last_of("/") + 1);
	this->folder = (path.find(".") == -1);
}