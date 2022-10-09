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
    
    float Quad[] = { 0.f,1.f,0.f, //X Cara1 
                     0.f,0.f,0.f,//Y 
                     0.f,0.f,1.f,//Z

                     0.0f,1.f,1.f,// Cara2
                     0.f,1.f,0.f, 
                     0.f,0.f,1.f,

                     1.f,1.f,0.f, //Cara3 
                     0.f,1.f,0.f,
                     0.f,1.f,1.f, 
                     
                     1.f,1.f,0.f, 
                     0.f,1.f,1.f,
                     1.f,1.f,1.f,
                        
                     0.f,0.f,1.f, // Cara4 
                     1.f,0.f,1.f,
                     0.f,1.f,1.f,
        
                     1.f,0.f,1.f,
                     1.f,1.f,1.f,
                     0.f,1.f,1.f,
                    
                     1.f, 0.f, 1.f,// Cara5
                     1.f, 0.f, 0.f,
                     1.f, 1.f, 0.f,
                     
                     1.f, 0.f, 1.f,
                     1.f, 1.f, 0.f,
                     1.f, 1.f, 1.f,
        
                     0.f, 0.f, 0.f, // cara6
                     0.f, 1.f, 0.f,
                     1.f, 1.f, 0.f,
                     
                     0.f, 0.f, 0.f,
                     1.f, 1.f, 0.f,
                     1.f, 0.f, 0.f,
        
                     0.f, 0.f, 0.f, // cara7
                     1.f, 0.f, 0.f,
                     1.f, 0.f, 1.f,
                     
                     1.f, 0.f, 1.f,
                     0.f, 0.f, 1.f,
                     0.f, 0.f, 0.f,
    };
       
    if (App->imguiwindows->Wireframe == true) {
        //Wireframe Mode
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          glLineWidth(2);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Quad);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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