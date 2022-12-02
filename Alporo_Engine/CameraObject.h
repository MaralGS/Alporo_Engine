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
	void Update();
	bool CleanUp();
	bool freeMovement = true;
	void Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference = false);
	void CreateCamBuffer();
	float* GetViewMatrix();
	~CObject();

	vec3 newPos = { 0, 2, 4 };
	vec3 newRef = { 0, 2, 4 };

	void CalculateViewMatrices();

public:

	vec3 X, Y, Z, Position, Reference;

	mat4x4 ViewMatrix, ViewMatrixInverse;

	unsigned int cameraBuffer2;
	unsigned int frameBuffer2;
	unsigned int bufferObj2;

	Camera* NewCamera = nullptr;
};



