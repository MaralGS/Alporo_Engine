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

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	
	GameObject* CameraGameObject();
	GameObject* GameCamera;
	bool SetCamera = false;
	//float* GetViewMatrix();
private:

	//void CalculateViewMatrix();

public:
	bool CreateGameCamera = true;
	GameObject* SecondCamera;
	CObject* Mcamera;
private:

	//mat4x4 ViewMatrix, ViewMatrixInverse;
	bool FromReference = true;
};