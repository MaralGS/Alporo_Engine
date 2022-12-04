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

	pathToRename = "";
	Refresh = false;
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
			PrintAssetsMenu();
			ImGui::EndMenuBar();
		}

		PrintAssets();

		if (DeleteOption)
		{
			ImGui::Begin("FileMenu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

			if (ImGui::MenuItem("Delete"))
			{
				RemoveFile(FileInfo(fileSelected));
				Refresh = true;
				DeleteOption = false;
				fileSelected = "";
			}
			ImGui::End();
		}

		if (App->input->GetKey(SDL_SCANCODE_DELETE) && ImGui::IsWindowHovered())
		{
			RemoveFile(FileInfo(fileSelected));
			fileSelected = "";
			Refresh = true;
		}

		ImGui::End();


	return UPDATE_CONTINUE;
}

update_status ModuleFiles::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleFiles::PrintAssets()
{
	for (int i = 0; i < dirInfo.size(); i++)
	{
		FileInfo file = dirInfo[i];

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		if (file.path == fileSelected)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;


		if (pathToRename != file.path)
		{
			bool y = ImGui::TreeNodeEx((void*)(intptr_t)&file, treeNodeFlags, file.name.c_str());
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
					fileSelected = file.path;
				}
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
				{
					fileSelected = file.path;
					DeleteOption = true;
					ImGui::SetNextWindowPos(ImGui::GetMousePos());
				}
			}

			if (y)
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
		Refresh = true;
	}
	
	if (Refresh) {
		GetDirectoryInfo(currentPath.c_str());
		Refresh = false;
	}
}

void ModuleFiles::PrintAssetsMenu()
{
	string pa = currentPath;

	while (pa.size() != 0)
	{
		int pos = pa.find_first_of("/");

		if (pos == -1) {
			ImGui::Text(pa.c_str());
			break;
		}

		if (ImGui::Button(pa.substr(0, pos).c_str()))
		{
			// end = folder inside (ex: street)
			string end = pa.substr(0, pa.find_first_of("/"));

			// pathName = full path (ex: Assets/street)
			SetCurrentPath(currentPath.substr(0, currentPath.find(end) + end.size()).c_str());
			break;
		}

		ImGui::Text("->");

		pa = pa.substr(pos + 1);
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
	char** i = PHYSFS_enumerateFiles(file.path.c_str());

	//Recursive deleting
	if (i[0] != NULL) {
		for (int j = 0; i[j] != NULL; j++) {
			string auxpath = file.path;
			FileInfo f(auxpath.append("/").append(i[j]).c_str());
			PHYSFS_setWriteDir(file.path.c_str());
			RemoveFile(f);
		}
	}


	string writedir = file.path.substr(0, file.path.find_last_of("/"));
	PHYSFS_setWriteDir(writedir.c_str());
	PHYSFS_delete(file.name.c_str());
}

void ModuleFiles::GetDirectoryInfo(const char* dir)
{
	dirInfo.clear();

	char** docs = PHYSFS_enumerateFiles(dir);

	//First add folders
	for (int i = 0; docs[i] != NULL; i++) {
		string d = dir;
		d.append("/").append(docs[i]);

		FileInfo f(d);
		if (f.folder) dirInfo.push_back(f);
	}

	//Next add files
	for (int i = 0; docs[i] != NULL; i++) {
		string d = dir;
		d.append("/").append(docs[i]);

		FileInfo f(d);
		if (!f.folder) dirInfo.push_back(f);
	}

	PHYSFS_freeList(docs);
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

	if (!folder) {
		this->extension = path.substr(path.find_last_of("."));
	}
	else {
		this->extension = "";
	}
}