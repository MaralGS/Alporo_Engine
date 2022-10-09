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

    DrawQuad();
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

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0,Quad);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // front face =================
    glEnd();

}
