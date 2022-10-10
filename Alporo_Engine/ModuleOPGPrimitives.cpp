#include "Globals.h"
#include "Application.h"
#include "ModuleOPGPrimitives.h"
#include "Primitive.h"
#include <gl/GL.h>

ModuleOPGPrimitives::ModuleOPGPrimitives(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleOPGPrimitives::~ModuleOPGPrimitives()
{

}


bool ModuleOPGPrimitives::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

bool ModuleOPGPrimitives::PreUpdate() {


	return true;
}

update_status ModuleOPGPrimitives::Update(float dt)
{
	if (DrawQuadra == true)
	{
		DrawQuad();
	}

	if (DrawPiramide == true)
	{
		DrawPiramid();
	}
	
	if (DrawCilindre == true)
	{
		DrawCilind(Radius,Leght);
	}



	return UPDATE_CONTINUE;
}

bool ModuleOPGPrimitives::PostUpdate() {

	

	return true;
}

bool ModuleOPGPrimitives::CleanUp()
{
	LOG("Unloading Intro scene");
	glDisableClientState(GL_VERTEX_ARRAY);
	return true;
}

void ModuleOPGPrimitives::DrawQuad()
{
	if (App->imguiwindows->Wireframe == true) {
		//Wireframe Mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
	}
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0,Quad);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // front face =================
    glEnd();

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

void ModuleOPGPrimitives::DrawPiramid()
{
	if (App->imguiwindows->Wireframe == true) {
		//Wireframe Mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, Triangle);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glVertexPointer(3, GL_FLOAT, 0, TriangleBase);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// front face =================
	glEnd();
}
