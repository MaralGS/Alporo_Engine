#include "Globals.h"
#include "Application.h"
#include "ModuleAssets.h"
#include "Globals.h"


ModuleAssets::ModuleAssets(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAssets::~ModuleAssets()
{}


bool ModuleAssets::Start()
{
	bool ret = true;


	return ret;
}

update_status ModuleAssets::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status ModuleAssets::Update(float dt)
{

	ImGui::Begin("AssetsWindow");
	{

	}
	ImGui::End();


	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleAssets::CleanUp()
{
	LOG(LogType::ERRORS, "Unloading Intro Assets");

	return true;
}

int ModuleAssets::Find(const char* file_in_assets) const
{
	return 0;
}

int ModuleAssets::ImportFile(const char* new_file_in_assets, Resource::Type type)
{
	Resource* resource = CreateNewResource(new_file_in_assets, type);
	int ret = 0;
	char* fileBuffer = nullptr;//Engine->fileSystem->Load(assetsFile); 
	switch (resource->GetType()) {
	//case Resource::texture: App->tex->Import(fileBuffer, resource); break;
	case Resource::Type::scene: App->scene->Import(fileBuffer, resource); break;
	case Resource::Type::mesh: App->meshes->Import(fileBuffer, resource); break;
	}
	//SaveResource(resource);
	ret = resource->GetUID();
	RELEASE_ARRAY(fileBuffer);
	UnloadResource(ret); 
	return ret;
	return 0;
}

int ModuleAssets::GenerateNewUID()
{
	return 0;
}

const Resource* ModuleAssets::RequestResource(int uid) const
{
	std::map<int, Resource*>::iterator it = resources.find(uid);
	if (it != resources.end())
	{
		it->second->referenceCount++;
		return it->second;
	}

	return nullptr;
}

Resource* ModuleAssets::RequestResource(int uid)
{
	return nullptr;
}

void ModuleAssets::UnloadResource(int uid)
{
	/*Resource* res = nullptr;

	std::map<int, Resource*>::iterator it = resources.find(uid);
	if (it == resources.end())
		return;

	res = it->second;
	res->DecreaseReferenceCount();

	if (res->GetReferenceCount() <= 0)
		ReleaseResource(res->GetUID());*/
}

void ModuleAssets::ReleaseResource(int uid)
{
}

Resource* ModuleAssets::CreateNewResource(const char* assetsFile, Resource::Type type)
{

	Resource* ret = nullptr;
	UID uid = GenerateNewUID();
	switch (type) {
	case Resource::texture: ret = (Resource*) new ResourceTexture(uid); break;
	case Resource::mesh: ret = (Resource*) new ResourceMesh(uid); break;
	case Resource::scene: ret = (Resource*) new ResourceScene(uid); break;
	case Resource::bone: ret = (Resource*) new ResourceBone(uid); break;
	case Resource::animation: ret = (Resource*) new ResourceAnimation(uid); break;
	}
	if (ret != nullptr)
	{
		resources[uid] = ret;
		resource->assetsFile = assetsPath;
		resource->libraryFile = GenLibraryPath(resource);
	}
	return ret;


	return nullptr;
}
