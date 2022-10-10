#pragma once

#include "Module.h"
#include "Globals.h"


class ModuleOPGPrimitives : public Module
{
public:
	ModuleOPGPrimitives(Application* app, bool start_enabled = true);
	~ModuleOPGPrimitives();

	bool Start();
	bool PostUpdate();
	update_status Update(float dt);
	bool PreUpdate();
	bool CleanUp();
    void DrawQuad();
    void DrawCircle(float radius);

	float Quad[108] = { 0.f,1.f,0.f, //X Cara1 
                     0.f,0.f,0.f,//Y 
                     0.f,0.f,1.f,//Z

                     0.0f,1.f,1.f,
                     0.f,1.f,0.f,
                     0.f,0.f,1.f,

                     1.f,1.f,0.f, //Cara2
                     0.f,1.f,0.f,
                     0.f,1.f,1.f,

                     1.f,1.f,0.f,
                     0.f,1.f,1.f,
                     1.f,1.f,1.f,

                     0.f,0.f,1.f, // Cara3 
                     1.f,0.f,1.f,
                     0.f,1.f,1.f,

                     1.f,0.f,1.f,
                     1.f,1.f,1.f,
                     0.f,1.f,1.f,

                     1.f, 0.f, 1.f,// Cara4
                     1.f, 0.f, 0.f,
                     1.f, 1.f, 0.f,

                     1.f, 0.f, 1.f,
                     1.f, 1.f, 0.f,
                     1.f, 1.f, 1.f,

                     0.f, 0.f, 0.f, // cara5
                     0.f, 1.f, 0.f,
                     1.f, 1.f, 0.f,

                     0.f, 0.f, 0.f,
                     1.f, 1.f, 0.f,
                     1.f, 0.f, 0.f,

                     0.f, 0.f, 0.f, // cara6
                     1.f, 0.f, 0.f,
                     1.f, 0.f, 1.f,

                     1.f, 0.f, 1.f,
                     0.f, 0.f, 1.f,
                     0.f, 0.f, 0.f,
    };

private:



};
