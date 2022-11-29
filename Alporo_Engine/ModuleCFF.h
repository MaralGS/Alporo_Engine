#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>
using namespace std;


class MoudleCFF : public Module
{
public:

	bool Start();
	void MeshSave(MyMesh* mesh);
	void MeshLoad(MyMesh* mesh);
	update_status PostUpdate(float dt);
	//bool Init();
	bool CleanUp();

private:

};