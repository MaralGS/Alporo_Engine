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
    /*
    //glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(10.f, 10.f, 10.f);
    glEnd();
    //glLineWidth(6.0f);
	*/
    
    float Quad[] = { 0.f,0.5f,0.f, //Y
                     0.f,0.f,0.f,//X Cara1
                     0.f,0.f,0.5f,//Z
                     0.0f,0.5f,0.5f,//X Cara2
                     0.f,0.5f,0.f, //Y 

                     0.f,0.f,0.5f,
                     0.f,0.5f,0.f, //Y Cara3
                     0.0f,0.5f,0.5f,//X
                     0.f,0.f,0.5f, }; 
    
 
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Quad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
    // front face =================
   

        glEnd();
	return UPDATE_CONTINUE;
}

bool ModuleOPGPrimitives::PostUpdate() {


	return true;
}

bool ModuleOPGPrimitives::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}