#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class GameObject;

struct Camera {
	vec3 X, Y, Z, Position, Reference;
	
};

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
	float* GetViewMatrix();
	GameObject* CameraGameObject();
	GameObject* GameCamera;
private:

	void CalculateViewMatrix();

public:
	Camera Cam;
	bool CreateGameCamera = true;
	GameObject* SeconCamera;
private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
	bool FromReference = true;
};