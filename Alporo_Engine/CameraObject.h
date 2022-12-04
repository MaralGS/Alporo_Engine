#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"
#include "Camera.h"
#include "glmath.h"

class GameObject;
class Component;

class CObject : public Component {
public:

	CObject();
	CObject(GameObject* GOCamera);
	bool Start();
	bool CleanUp();
	void CreateCamBuffer();
	void SetCam();
	float* GetViewMatrix();
	~CObject();
	float* CalculateProjMatix();
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);

public:

	Frustum CamFrust;
	float4x4 ViewMatrix, ViewMatrixproj;

	unsigned int bufferCam;
	unsigned int frameBuffer;
	unsigned int bufferObj;
};



