#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class GameObject;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();


	GameObject* CameraGameObject();
	//GameObject* GameCamera;
	//float* GetViewMatrix();
private:

	//void CalculateViewMatrix();

public:
	bool CreateGameCamera = true;
	//GameObject* SecondCamera;
	CObject* Mcamera;

private:

	//mat4x4 ViewMatrix, ViewMatrixInverse;
	bool FromReference = true;
};