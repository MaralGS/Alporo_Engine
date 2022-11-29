#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>
using namespace std;


class MoudleCFF : public Module
{
public:

	bool Start();
	const char* MeshSave(MyMesh* mesh);
	void MeshLoad(const char* path);
	update_status PostUpdate(float dt);
	//bool Init();
	bool CleanUp();

private:

};