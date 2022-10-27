#include "Globals.h"
#include "Application.h"
#include "ModuleOPGPrimitives.h"
#include "Primitive.h"
#include <glew.h>
#include <gl/GL.h>

ModuleOPGPrimitives::ModuleOPGPrimitives(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleOPGPrimitives::~ModuleOPGPrimitives()
{

}


bool ModuleOPGPrimitives::Start()
{
	LOG(LogType::LOGS, "Loading Intro primitive");
	bool ret = true;

	return ret;
}

bool ModuleOPGPrimitives::PreUpdate() {


	return true;
}

update_status ModuleOPGPrimitives::Update(float dt)
{
	//Create Quad
	for (int i = 0; i < NumQuads; i++){
		DrawQuad(Cub[i]);
		if (PM == 1)
		{
			QuadKeys(Cub[App->imguiwindows->CubPicked], dt);
		}
	}
	

	//Create Piramid
	for (int i = 0; i < NumPiramid; i++)
	{
		DrawPiramid(Piramid[i]);
		if (PM == 2)
		{
			PiramidKeys(Piramid[App->imguiwindows->PiramidPicked], dt);
		}
		
	}

	
	
	if (CilindreStats.DrawCilindre == true)
	{
		DrawCilind(CilindreStats.Radius, CilindreStats.Leght);
	}

	return UPDATE_CONTINUE;
}

bool ModuleOPGPrimitives::PostUpdate() {

	

	return true;
}

bool ModuleOPGPrimitives::CleanUp()
{
	LOG(LogType::LOGS, "Unloading Intro scene");
	glDisableClientState(GL_TRIANGLES);
	glDisableClientState(GL_POLYGON);
	glDisableClientState(GL_QUAD_STRIP);
	return true;
}

void ModuleOPGPrimitives::DrawQuad(Quad* Q)
{
	if (App->imguiwindows->Wireframe == true) {
		//Wireframe Mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
	}
    	
	glBegin(GL_TRIANGLES);  // draw a cube with 12 triangles

	glVertex3fv(Q->v0);    //Cara1
	glVertex3fv(Q->v1);
	glVertex3fv(Q->v2);

	glVertex3fv(Q->v2);    // v2-v3-v0
	glVertex3fv(Q->v3);
	glVertex3fv(Q->v0);

	glVertex3fv(Q->v0);    //Cara2
	glVertex3fv(Q->v3);
	glVertex3fv(Q->v4);

	glVertex3fv(Q->v3);
	glVertex3fv(Q->v5);
	glVertex3fv(Q->v4);
	

	glVertex3fv(Q->v2); //Cara3
	glVertex3fv(Q->v5);
	glVertex3fv(Q->v3);

	glVertex3fv(Q->v2);
	glVertex3fv(Q->v6);
	glVertex3fv(Q->v5);
	
	glVertex3fv(Q->v6);//Cara4
	glVertex3fv(Q->v4);
	glVertex3fv(Q->v5);
	
	glVertex3fv(Q->v6);
	glVertex3fv(Q->v7);
	glVertex3fv(Q->v4);
	
	glVertex3fv(Q->v7);//Cara5
	glVertex3fv(Q->v0);
	glVertex3fv(Q->v4);

	glVertex3fv(Q->v7);
	glVertex3fv(Q->v1);
	glVertex3fv(Q->v0);
	
	glVertex3fv(Q->v1);//Cara6
	glVertex3fv(Q->v6);
	glVertex3fv(Q->v2);
	
	glVertex3fv(Q->v1);
	glVertex3fv(Q->v7);
	glVertex3fv(Q->v6);
	glEnd();

	/* glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0,Quad);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// front face =================
	glEnd();*/
}

void ModuleOPGPrimitives::DrawCilind(float radius, float leght)
{

	int n = 30;

	// Cylinder Bottom
	glBegin(GL_POLYGON);

	for (int i = 360; i >= 0; i -= (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians
		float X = -leght * 0.5f;
		float Y = radius * cos(a);
		float Z = radius * sin(a);
		glVertex3f(X, Y, Z);
	}
	glEnd();
	// Cylinder Top
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 360; i >= 0; i -= (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians
		float X = leght * 0.5f;
		float Y = radius * cos(a);
		float Z = -radius * sin(a);
		glVertex3f(X, Y, Z);
	}
	glEnd();

	// Cylinder "Cover"
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < 480; i += (360 / n))
	{
		float a = i * M_PI / 180; // degrees to radians

		glVertex3f(leght * 0.5f, radius * cos(a), radius * sin(a));
		glVertex3f(-leght * 0.5f, radius * cos(a), radius * sin(a));
	}
	glEnd();
}

void ModuleOPGPrimitives::DrawPiramid(Triangle* P)
{
	if (App->imguiwindows->Wireframe == true) {
		//Wireframe Mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
	}

	glBegin(GL_TRIANGLES);  // draw a triangle

	glVertex3fv(P->v0);    //Cara1
	glVertex3fv(P->v1);
	glVertex3fv(P->v2);

	glVertex3fv(P->v3);    //Cara2
	glVertex3fv(P->v2);
	glVertex3fv(P->v1);

	glVertex3fv(P->v3);    //Cara3
	glVertex3fv(P->v4);
	glVertex3fv(P->v2);

	glVertex3fv(P->v4);    //Cara4
	glVertex3fv(P->v0);
	glVertex3fv(P->v2);
	
	glVertex3fv(P->v4);    //Base
	glVertex3fv(P->v3);
	glVertex3fv(P->v1);
	
	glVertex3fv(P->v4);
	glVertex3fv(P->v1);
	glVertex3fv(P->v0);

	glEnd();
}

void ModuleOPGPrimitives::DrawSphere(float radius)
{

}

void ModuleOPGPrimitives::QuadKeys(Quad* Q, float dt)
{
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT && PM == 1)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			Q->Pos.x = (Q->Pos.x + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
		{
			Q->Pos.x = (Q->Pos.x - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			Q->Pos.y = (Q->Pos.y + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			Q->Pos.y = (Q->Pos.y - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT)
		{
			Q->Pos.z = (Q->Pos.z + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
		{
			Q->Pos.z = (Q->Pos.z - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP || App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP)
		{
			Q->Pos.x = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP || App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
		{
			Q->Pos.y = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP || App->input->GetKey(SDL_SCANCODE_X) == KEY_UP)
		{
			Q->Pos.z = 0;
		}

	}

	
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			Q->v0[i] += Q->Pos.x;
			Q->v1[i] += Q->Pos.x;
			Q->v2[i] += Q->Pos.x;
			Q->v3[i] += Q->Pos.x;
			Q->v4[i] += Q->Pos.x;
			Q->v5[i] += Q->Pos.x;
			Q->v6[i] += Q->Pos.x;
			Q->v7[i] += Q->Pos.x;
		}
		if (i == 1)
		{
			Q->v0[i] += Q->Pos.y;
			Q->v1[i] += Q->Pos.y;
			Q->v2[i] += Q->Pos.y;
			Q->v3[i] += Q->Pos.y;
			Q->v4[i] += Q->Pos.y;
			Q->v5[i] += Q->Pos.y;
			Q->v6[i] += Q->Pos.y;
			Q->v7[i] += Q->Pos.y;
		}
		if (i == 2)
		{
			Q->v0[i] += Q->Pos.z;
			Q->v1[i] += Q->Pos.z;
			Q->v2[i] += Q->Pos.z;
			Q->v3[i] += Q->Pos.z;
			Q->v4[i] += Q->Pos.z;
			Q->v5[i] += Q->Pos.z;
			Q->v6[i] += Q->Pos.z;
			Q->v7[i] += Q->Pos.z;
		}
	}
}

void ModuleOPGPrimitives::PiramidKeys(Triangle* Q, float dt)
{
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT && PM == 2)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			Q->Pos.x = (Q->Pos.x + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
		{
			Q->Pos.x = (Q->Pos.x - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			Q->Pos.y = (Q->Pos.y + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			Q->Pos.y = (Q->Pos.y - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT)
		{
			Q->Pos.z = (Q->Pos.z + 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT)
		{
			Q->Pos.z = (Q->Pos.z - 0.1) * (5.0f * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP || App->input->GetKey(SDL_SCANCODE_Q) == KEY_UP)
		{
			Q->Pos.x = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP || App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
		{
			Q->Pos.y = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP || App->input->GetKey(SDL_SCANCODE_X) == KEY_UP)
		{
			Q->Pos.z = 0;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			Q->v0[i] += Q->Pos.x;
			Q->v1[i] += Q->Pos.x;
			Q->v2[i] += Q->Pos.x;
			Q->v3[i] += Q->Pos.x;
			Q->v4[i] += Q->Pos.x;
		}
		if (i == 1)
		{
			Q->v0[i] += Q->Pos.y;
			Q->v1[i] += Q->Pos.y;
			Q->v2[i] += Q->Pos.y;
			Q->v3[i] += Q->Pos.y;
			Q->v4[i] += Q->Pos.y;
		}
		if (i == 2)
		{
			Q->v0[i] += Q->Pos.z;
			Q->v1[i] += Q->Pos.z;
			Q->v2[i] += Q->Pos.z;
			Q->v3[i] += Q->Pos.z;
			Q->v4[i] += Q->Pos.z;
		}
	}
}

