#include "CameraObject.h"
#include "imgui.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_events.h"

CObject::CObject() : CObject(nullptr)
{

	CalculateViewMatrices();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

	glGenFramebuffers(1, &frameBuffer2);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer2);

	glGenTextures(1, &cameraBuffer2);
	glBindTexture(GL_TEXTURE_2D, cameraBuffer2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cameraBuffer2, 0);

	glGenRenderbuffers(1, &bufferObj2);
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObj2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bufferObj2);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CObject::CObject(GameObject* GOCamera) : Component(GOCamera)
{
	GObjectSelected = GOCamera;
	type = Type::CamObject;
}

CObject::~CObject()
{

}

update_status CObject::Update(float dt)
{

	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!
	SDL_Event e;
	bool quit = false;

	float speed = 3.0f * dt;

	
	Position = newPos;

	// Recalculate matrix -------------
	CalculateViewMatrices();

	return UPDATE_CONTINUE;
}

bool CObject::CleanUp()
{
	return false;
}

void CObject::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{

	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrices();

}

float* CObject::GetViewMatrix()
{
	return &ViewMatrix;
}

void CObject::CalculateViewMatrices()
{

	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);

}