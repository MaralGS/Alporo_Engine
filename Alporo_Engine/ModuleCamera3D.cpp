#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Transform.h"
#include "CameraObject.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG(LogType::LOGS, "Setting up the camera");
	bool ret = true;

	//creating GameCamera

	Mcamera = new CObject();
	Mcamera->CamFrust.pos = float3(0, 1, -30);
	CameraGameObject();
	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG(LogType::LOGS,"Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can vecmake this movememnt frame rate independant!
	if (App->imguiwindows->Selected != GameCamera)
	{
		float speed = 5.0f * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 10.0f * dt;

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) Mcamera->CamFrust.pos += Mcamera->CamFrust.front * speed;
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) Mcamera->CamFrust.pos -= Mcamera->CamFrust.front * speed;

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) Mcamera->CamFrust.pos -= Mcamera->CamFrust.WorldRight() * speed;
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)Mcamera->CamFrust.pos += Mcamera->CamFrust.WorldRight() * speed;
		}



		if (App->input->GetMouseZ() >= 0)
		{
			Mcamera->CamFrust.pos -= Mcamera->CamFrust.front * speed;
		}

		if (App->input->GetMouseZ() <= 0)
		{
			Mcamera->CamFrust.pos += Mcamera->CamFrust.front * speed;
		}

		// Mouse motion ----------------

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;
			Quat reference;
			Mcamera->CamFrust.WorldMatrix().Decompose(float3(), reference, float3());

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				Quat X = Quat::identity;
				X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);

				reference = X * reference;
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;
				Quat Y = Quat::identity;
				Y.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DeltaY * DEGTORAD);
				reference = reference * Y;
			}

			float4x4 matrix = Mcamera->CamFrust.WorldMatrix();
			matrix.SetRotatePart(reference.Normalized());
			Mcamera->CamFrust.SetWorldMatrix(matrix.Float3x4Part());
		}


		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
			if (App->imguiwindows->Selected != nullptr)
			{
				Mcamera->CamFrust.pos = float3(App->imguiwindows->Selected->transform->position.x, App->imguiwindows->Selected->transform->position.y + 2, App->imguiwindows->Selected->transform->position.z - 5);
				Mcamera->LookAt(App->imguiwindows->Selected->transform->position);
			}
		}
	}
		

		if (App->imguiwindows->Selected == GameCamera)
		{
			Ccamera->CamFrust.pos = GameCamera->transform->position;
		}

	return UPDATE_CONTINUE;
}

GameObject* ModuleCamera3D::CameraGameObject()
{

	GameCamera = App->LoadFbx->LoadFile("Assets/Primitives/cube2.fbx", "GameCamera");

	CObject* CompCam = new CObject(GameCamera);
	Ccamera = CompCam;
	GameCamera->Comp.push_back(CompCam);
	GameCamera->transform->position = float3(0, 1, -5);
	return nullptr;
}
