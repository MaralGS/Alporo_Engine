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
	//SecondCamera = CameraGameObject();
	Mcamera = new CObject();
	Mcamera->CamFrust.pos = float3(0.0f, 0.0f, 5.0f);
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

		float speed = 5.0f * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 10.0f * dt;
		
			if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			{
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) Mcamera->CamFrust.pos += Mcamera->CamFrust.front * speed;
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) Mcamera->CamFrust.pos -= Mcamera->CamFrust.front * speed;
																				
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) Mcamera->CamFrust.pos += Mcamera->CamFrust.WorldRight() * speed;
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)Mcamera->CamFrust.pos -= Mcamera->CamFrust.WorldRight() * speed;
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
				X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX);

			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;
				Quat Y = Quat::identity;
				Y.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DeltaY);

			}

			float4x4 matrix = Mcamera->CamFrust.WorldMatrix();
			matrix.SetRotatePart(reference.Normalized());
			Mcamera->CamFrust.SetWorldMatrix(matrix.Float3x4Part());
		}

		/*if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();
			vec3 NRef;
			float Sensitivity = 0.25f;

			if (dx != 0)
			{
				float DeltaX = (float)dx * Sensitivity;

				Cam.X = rotate(Cam.X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Cam.Y = rotate(Cam.Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				Cam.Z = rotate(Cam.Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			}

			if (dy != 0)
			{
				float DeltaY = (float)dy * Sensitivity;

				Cam.Y = rotate(Cam.Y, DeltaY, Cam.X);
				Cam.Z = rotate(Cam.Z, DeltaY, Cam.X);

				if (Cam.Y.y < 0.0f)
				{
					Cam.Z = vec3(0.0f, Cam.Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
					Cam.Y = cross(Cam.Z, Cam.X);
				}
			}

		}*/

		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
			if (App->imguiwindows->Selected != nullptr)
			{
				Mcamera->CamFrust.pos = App->imguiwindows->Selected->transform->position;
				Mcamera->LookAt(Mcamera->CamFrust.pos);
			}
		}


	return UPDATE_CONTINUE;
}

GameObject* ModuleCamera3D::CameraGameObject()
{
	//GameCamera = new GameObject(App->imguiwindows->RootGO);
	//GameCamera->name = "Game Camera";
	
	return nullptr;
}
