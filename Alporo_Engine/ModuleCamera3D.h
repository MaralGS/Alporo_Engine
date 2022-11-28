#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

class GameObject;

struct Camera {
	float3 X, Y, Z, Position, Reference;
	GameObject* SecCamera;
};

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const float3&Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3&Spot);
	void Move(const float3&Movement);
	float* GetViewMatrix();
	GameObject* CameraGameObject();
	GameObject* GameCamera;
private:

	void CalculateViewMatrix();

public:
	Camera Cam;
	bool CreateGameCamera = true;
	GameObject* SecondCamera;
private:

	float4x4 ViewMatrix, ViewMatrixInverse;
	bool FromReference = true;
};