#include "CameraObject.h"
#include "imgui.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_events.h"

CObject::CObject()
{

	CreateCamBuffer();
	CamFrust.pos = float3(0.0f, 0.0f, 5.0f);
	//CamFrust.referenceReference = float3(0.0f, 0.0f, 0.0f);

}

CObject::CObject(GameObject* GOCamera) : Component(GOCamera)
{
	GObjectSelected = GOCamera;
	type = Type::CamObject;
}

bool CObject::Start()
{

	return false;
}

CObject::~CObject()
{
	glDeleteFramebuffers(1, &bufferCam);
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteFramebuffers(1, &bufferObj);
}

bool CObject::CleanUp()
{
	return false;
}

void CObject::CreateCamBuffer()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &bufferCam);
	glBindTexture(GL_TEXTURE_2D, bufferCam);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferCam, 0);

	glGenRenderbuffers(1, &bufferObj);
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObj);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bufferObj);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// -----------------------------------------------------------------
/*void ModuleCamera3D::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{
	this->Cam.Position = Position;
	this->Cam.Reference = Reference;

	Cam.Z = normalize(Position - Reference);
	Cam.X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Cam.Z));
	Cam.Y = cross(Cam.Z, Cam.X);

	if (!RotateAroundReference)
	{
		this->Cam.Reference = this->Cam.Position;
		this->Cam.Position += Cam.Z * 0.05f;
	}

	CalculateViewMatrix();
}*/

// -----------------------------------------------------------------
void CObject::LookAt(const float3& Spot)
{
	CamFrust.front = (Spot - CamFrust.pos).Normalized();
	float3 pos = float3(0, 1, 0).Cross(CamFrust.front).Normalized();
	CamFrust.up = CamFrust.front.Cross(pos);
}

// -----------------------------------------------------------------
void CObject::Move(const float3& Movement)
{
	CamFrust.pos += Movement;
}

float* CObject::GetViewMatrix()
{
	ViewMatrix = CamFrust.ViewMatrix();
	ViewMatrix.Transpose();
	return ViewMatrix.ptr();
}

float* CObject::CalculateProjMatix()
{
	ViewMatrixproj = CamFrust.ProjectionMatrix();
	ViewMatrixproj.Transpose();
	return ViewMatrixproj.ptr();
}

