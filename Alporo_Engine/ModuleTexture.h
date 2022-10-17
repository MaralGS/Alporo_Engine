#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"

#define CHECKERS_HEIGHT 256
#define CHECKERS_WIDTH 256

class ModuleTexture : public Module
{
public:
    ModuleTexture(Application* app, bool start_enabled = true);
    ~ModuleTexture();

    bool Start();
    bool PostUpdate();
    update_status Update(float dt);
    bool PreUpdate();
    bool CleanUp();
    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    GLuint textureID;
private:
 
};
