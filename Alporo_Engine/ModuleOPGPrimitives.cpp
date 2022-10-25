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
	if (DrawQuadra == true)
	{
		DrawQuad();
	}

	if (DrawPiramide == true)
	{
		DrawPiramid();
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

void ModuleOPGPrimitives::DrawQuad()
{
	if (App->imguiwindows->Wireframe == true) {
		//Wireframe Mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
	}
   /* glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0,Quad);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // front face =================
    glEnd();*/
	 
	Quad Q;
	
	glBegin(GL_TRIANGLES);  // draw a cube with 12 triangles

	glVertex3fv(Q.v0);    //Cara1
	glVertex3fv(Q.v1);
	glVertex3fv(Q.v2);

	glVertex3fv(Q.v2);    // v2-v3-v0
	glVertex3fv(Q.v3);
	glVertex3fv(Q.v0);

	glVertex3fv(Q.v0);    //Cara2
	glVertex3fv(Q.v3);
	glVertex3fv(Q.v4);

	glVertex3fv(Q.v3);
	glVertex3fv(Q.v5);
	glVertex3fv(Q.v4);
	

	glVertex3fv(Q.v2); //Cara3
	glVertex3fv(Q.v5);
	glVertex3fv(Q.v3);

	glVertex3fv(Q.v2);   
	glVertex3fv(Q.v6);
	glVertex3fv(Q.v5);
	
	glVertex3fv(Q.v6);//Cara4
	glVertex3fv(Q.v4);
	glVertex3fv(Q.v5);
	
	glVertex3fv(Q.v6); 
	glVertex3fv(Q.v7);
	glVertex3fv(Q.v4);
	
	glVertex3fv(Q.v7);//Cara5
	glVertex3fv(Q.v0);
	glVertex3fv(Q.v4);
	
	glVertex3fv(Q.v7); 
	glVertex3fv(Q.v1);
	glVertex3fv(Q.v0);
	
	glVertex3fv(Q.v1);//Cara6
	glVertex3fv(Q.v6);
	glVertex3fv(Q.v2);
	
	glVertex3fv(Q.v1); 
	glVertex3fv(Q.v7);
	glVertex3fv(Q.v6);

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
	Triangle T;

	glBegin(GL_TRIANGLES);  // draw a triangle

	glVertex3fv(T.v0);    //Cara1
	glVertex3fv(T.v1);
	glVertex3fv(T.v2);

	glVertex3fv(T.v3);    //Cara2
	glVertex3fv(T.v2);
	glVertex3fv(T.v1);

	glVertex3fv(T.v3);    //Cara3
	glVertex3fv(T.v4);
	glVertex3fv(T.v2);

	glVertex3fv(T.v4);    //Cara4
	glVertex3fv(T.v0);
	glVertex3fv(T.v2);
	
	glVertex3fv(T.v4);    //Base
	glVertex3fv(T.v3);
	glVertex3fv(T.v1);
	
	glVertex3fv(T.v4);    
	glVertex3fv(T.v1);
	glVertex3fv(T.v0);

	glEnd();
}

void ModuleOPGPrimitives::DrawSphere(float radius)
{

}
