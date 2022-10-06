#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleOPGPrimitives : public Module
{
public:
	ModuleOPGPrimitives(Application* app, bool start_enabled = true);
	~ModuleOPGPrimitives();

	bool Start();
	bool PostUpdate();
	update_status Update(float dt);
	bool PreUpdate();
	bool CleanUp();

private:
	/*
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
	GLfloat v4;
	GLfloat v5;
	GLfloat v6;
	*/

};
