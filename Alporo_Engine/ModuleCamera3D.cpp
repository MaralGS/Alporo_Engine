#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Transform.h"
#include "CameraObject.h"



ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	Cam.X = vec3(1.0f, 0.0f, 0.0f);
	Cam.Y = vec3(0.0f, 1.0f, 0.0f);
	Cam.Z = vec3(0.0f, 0.0f, 1.0f);

	Cam.Position = vec3(0.0f, 0.0f, 5.0f);
	Cam.Reference = vec3(0.0f, 0.0f, 0.0f);

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG(LogType::LOGS, "Setting up the camera");
	bool ret = true;

	//creating GameCamera
	SecondCamera = CameraGameObject();

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

		vec3 newPos(0, 0, 0);
		float speed = 5.0f * dt;
		if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			speed = 10.0f * dt;
		if (App->imguiwindows->Selected != GameCamera)
		{
			if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			{
				if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Cam.Z * speed;
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Cam.Z * speed;


				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= Cam.X * speed;
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += Cam.X * speed;
			}
			SetCamera = true;
		}


		if (App->input->GetMouseZ() >= 0)
		{
			newPos -= Cam.Z * speed;
		}

		if (App->input->GetMouseZ() <= 0)
		{
			newPos += Cam.Z * speed;
		}

		Cam.Position += newPos;
		Cam.Reference += newPos;

		// Mouse motion ----------------

		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
		{
			int dx = -App->input->GetMouseXMotion();
			int dy = -App->input->GetMouseYMotion();

			float Sensitivity = 0.25f;

			Cam.Position -= Cam.Reference;

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

			Cam.Position = Cam.Reference + Cam.Z * length(Cam.Position);
		}

		if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
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

		}

		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
			if (App->imguiwindows->Selected != nullptr)
			{
				newPos.x = App->imguiwindows->Selected->transform->position.x;
				newPos.y = App->imguiwindows->Selected->transform->position.y;
				newPos.z = App->imguiwindows->Selected->transform->position.z;
				LookAt(newPos);
			}
		}



		// Recalculate matrix -------------
		CalculateViewMatrix();
		if (App->imguiwindows->Selected == GameCamera)
		{
			Cam.Position.x = GameCamera->transform->position.x;
			Cam.Position.y = GameCamera->transform->position.y;
			Cam.Position.z = GameCamera->transform->position.z;
		}
	

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Cam.Position = Position;
	this->Cam.Reference = Reference;

	Cam.Z = normalize(Position - Reference);
	Cam.X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Cam.Z));
	Cam.Y = cross(Cam.Z, Cam.X);

	if(!RotateAroundReference)
	{
		this->Cam.Reference = this->Cam.Position;
		this->Cam.Position += Cam.Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Cam.Reference = Spot;

	Cam.Z = normalize(Cam.Position - Cam.Reference);
	Cam.X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Cam.Z));
	Cam.Y = cross(Cam.Z, Cam.X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Cam.Position += Movement;
	Cam.Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

GameObject* ModuleCamera3D::CameraGameObject()
{
	GameCamera = new GameObject(App->imguiwindows->RootGO);
	GameCamera->name = "Game Camera";
	/*
	Camera* Scamera = new Camera();
	CObject* component = new CObject(GameCamera);
	Cam.SecCamera = GameCamera;
	component->NewCamera = Scamera;
	if (GameCamera->Comp.size() == 1) {
		GameCamera->Comp.push_back(component);
	}
	*/
	return nullptr;
}




// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(Cam.X.x, Cam.Y.x, Cam.Z.x, 0.0f, Cam.X.y, Cam.Y.y, Cam.Z.y, 0.0f, Cam.X.z, Cam.Y.z, Cam.Z.z, 0.0f, -dot(Cam.X, Cam.Position), -dot(Cam.Y, Cam.Position), -dot(Cam.Z, Cam.Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}
