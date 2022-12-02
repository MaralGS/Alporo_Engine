#include "CameraObject.h"
#include "imgui.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_events.h"

CObject::CObject() :CObject(nullptr)
{

}

CObject::CObject(GameObject* GOCamera) : Component(GOCamera)
{
	GObjectSelected = GOCamera;
	type = Type::CamObject;
	SecondGameCamera* GameCamera = new SecondGameCamera();
}

CObject::~CObject()
{

}

SecondGameCamera::SecondGameCamera()
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

SecondGameCamera::~SecondGameCamera()
{
}

bool SecondGameCamera::Start()
{
	return false;
}

update_status SecondGameCamera::Update(float dt)
{

	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!
	SDL_Event e;
	bool quit = false;

	float speed = 3.0f * dt;

	if (ImGui::IsKeyPressed(ImGuiKey_LeftShift)) {
		speed *= 2;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0) // scroll up
			{
				// Put code for handling "scroll up" here!
			}
			else if (event.wheel.y < 0) // scroll down
			{
				// Put code for handling "scroll down" here!
			}
		}
	}
	if (ImGui::IsKeyPressed(ImGuiKey_U)) newPos.y += speed;
	if (ImGui::IsKeyPressed(ImGuiKey_J)) newPos.y -= speed;

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
		if (ImGui::IsKeyPressed(ImGuiKey_W)) {
			freeMovement = true;
			newPos -= Z * speed;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_S)) {
			freeMovement = true;
			newPos += Z * speed;
		}


		if (ImGui::IsKeyPressed(ImGuiKey_A)) {
			freeMovement = true;
			newPos -= X * speed;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_D)) {
			freeMovement = true;
			newPos += X * speed;
		}
	}

	if (ImGui::GetMouseCursor >= 0) {
		newPos -= Z * zoomSensitivity;
	}
	if (ImGui::GetMouseCursor <= 0) {
		newPos += Z * zoomSensitivity;
	}

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Middle) && !ImGui::IsKeyPressed(ImGuiKey_LeftAlt))
	{
		int dx = -ImGui::GetMousePos().x;
		int dy = -ImGui::GetMousePos().y;

		float Sensitivity = 0.25f;


		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * 4;
		freeMovement = true;
	}

	Position = newPos;

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsKeyPressed(ImGuiKey_LeftAlt))
	{
		int dx = -ImGui::GetMousePos().x;
		int dy = -ImGui::GetMousePos().y;

		float Sensitivity = 0.25f;

		newRef.x = 0;
		newRef.y = 0;
		newRef.z = 0;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}


		Position = newRef + Z * (6);


		freeMovement = false;
	}

	if (freeMovement == false) {
		Look(Position, newRef);
	}
	if (ImGui::IsKeyPressed(ImGuiKey_F)) {

		newRef.x = 1;
		newRef.y = 2;
		newRef.z = 4;
		Look(newPos, { 0,0,0 });
		freeMovement = true;


	}

	// Recalculate matrix -------------
	CalculateViewMatrices();

	return UPDATE_CONTINUE;
}

bool SecondGameCamera::CleanUp()
{
	return false;
}

void SecondGameCamera::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
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

void SecondGameCamera::LookAt(const vec3& Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrices();
}

void SecondGameCamera::Move(const vec3& Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrices();
}

float* SecondGameCamera::GetViewMatrix()
{
	return &ViewMatrix;
}

void SecondGameCamera::CalculateViewMatrices()
{

	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);

}