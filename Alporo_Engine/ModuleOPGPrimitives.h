#pragma once
#include "Module.h"
#include "Globals.h"

struct Cilindre
{
    bool DrawCilindre = false;
    float Leght = 3;
    float Radius = 1;
};

struct Quad
{

    vec3 Pos;
    float v0[3] = { 0.f + Pos.x, 1.f + Pos.y, 0.f + Pos.z };
    float v1[3] = { 0.f + Pos.x, 0.f + Pos.y, 0.f + Pos.z };
    float v2[3] = { 0.f + Pos.x, 0.f + Pos.y, 1.f + Pos.z };
    float v3[3] = { 0.f + Pos.x, 1.f + Pos.y, 1.f + Pos.z };
    float v4[3] = { 1.f + Pos.x, 1.f + Pos.y, 0.f + Pos.z };
    float v5[3] = { 1.f + Pos.x, 1.f + Pos.y, 1.f + Pos.z };
    float v6[3] = { 1.f + Pos.x, 0.f + Pos.y, 1.f + Pos.z };
    float v7[3] = { 1.f + Pos.x, 0.f + Pos.y, 0.f + Pos.z };
};

struct Triangle
{
    vec3 Pos;
    float v0[3] = { 0.f,0.f,0.f };
    float v1[3] = { 2.f,0.f,0.f };
    float v2[3] = { 1.f,2.f,-1.f};
    float v3[3] = { 2.f, 0.f, -2.f };
    float v4[3] = { 0.f, 0.f, -2.f };
};

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
    void DrawQuad(Quad* Q);
    void DrawCilind(float radius, float leght);
    void DrawPiramid(Triangle* P);
    void DrawSphere(float radius);
    void QuadKeys(Quad* Q, float dt);
    void PiramidKeys(Triangle* Q, float dt);

  
    bool DrawPiramide = false;
  
    Cilindre CilindreStats;
    std::vector<Quad*> Cub;
    std::vector<Triangle*> Piramid;

    int NumQuads=0;
    int NumPiramid=0;
    int PM = 0;

private:
    //Quad posant el vertex a cada lloc
   /* float Quad[108] = {0.f,1.f,0.f, //X Cara1 
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
    };*/
    //Triangle posant el vertex a cada lloc
   /*float Triangl[36] = {0.f,0.f,0.f, //X Cara1 
                     2.f,0.f,0.f,//Y 
                     1.f,2.f,-1.f,//Z


                     2.f,0.f,-2.f, //Cara2
                     1.f,2.f,-1.f,
                     2.f,0.f,0.f,

                     2.f,0.f,-2.f, // Cara3 
                     0.f,0.f,-2.f,
                     1.f,2.f,-1.f,

                     0.f,0.f,-2.f, // Cara4 
                     0.f,0.f,-0.f,
                     1.f,2.f,-1.f,
    };

    float TriangleBas[18] = {

                     0.f, 0.f, -2.f,
                     2.f, 0.f, -2.f,
                     2.f, 0.f, 0.f,

                     0.f, 0.f, -2.f,
                     2.f, 0.f, 0.f,
                     0.f, 0.f, 0.f,
    };*/


};
