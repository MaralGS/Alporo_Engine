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
	void GameCameraMovement(GameObject* SecCamera);
	bool CleanUp();
	void CreateCamBuffer();
	float* GetViewMatrix();
	~CObject();

	float3 newPos = { 0, 0, 0 };
	float3 newRef = { 0, 2, 4 };

	void CalculateViewMatrices();

public:

	float3 X, Y, Z, Position, Reference;

	float4x4 ViewMatrix, ViewMatrixInverse;

	unsigned int cameraBuffer2;
	unsigned int frameBuffer2;
	unsigned int bufferObj2;

	Camera* NewCamera;
};



