#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Transform.h"
#include "Mesh.h"
#include "scene.h"
#include <vector>

#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}
bool ModuleLoadFBX::Start()
{
	bool ret = true;
	
	MeshObject = LoadFile("Assets/BakerHouse.fbx", "BakerHouse");
	
	return ret;
}

MyMesh::MyMesh() : id_indices(0), id_vertices(0)
{
}

MyMesh::~MyMesh() {
	delete[] vertices;
	delete[] indices;
	vertices = nullptr;
	indices = nullptr;
	glDeleteBuffers(1, &id_vertices);
	glDeleteBuffers(1, &id_indices);
	id_vertices = 0;
	id_indices = 0;
}
void MyMesh::Render()
{


	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glPushMatrix();
	glMultMatrixf(&OBmesh->transform->Transform_Matrix);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);

}

GameObject* ModuleLoadFBX::LoadFile(string file_path, string nameGO)
{
	const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* meshGO;
		if (App->imguiwindows->Selected == nullptr)
		{
			meshGO = new GameObject(App->imguiwindows->RootGO);
			meshGO->name = nameGO;
		}

		else if (App->imguiwindows->Selected != nullptr)
		{
			meshGO = new GameObject(App->imguiwindows->Selected);
			meshGO->name = nameGO;
		}

		for (int i = 0; i < scene->mNumMeshes; i++) {
			MyMesh* mesh = new MyMesh();

			//Copy fbx mesh info to Mesh struct
			mesh->num_vertices = scene->mMeshes[i]->mNumVertices;
			mesh->vertices = new float[mesh->num_vertices * 3];
			memcpy(mesh->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->num_vertices * 3);

			//Load Faces
			if (scene->mMeshes[i]->HasFaces())
			{

				mesh->num_indices = scene->mMeshes[i]->mNumFaces * 3;
				mesh->indices = new uint[mesh->num_indices]; // assume each face is a triangle

	
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					//Check that faces are triangles
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
					}
					else {
						memcpy(&mesh->indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
				LoadMesh(mesh);
				Meshes* component = new Meshes(meshGO);
				mesh->OBmesh = meshGO;
				component->mesh = mesh;
				if (meshGO->Comp.size() == 1) {
					meshGO->Comp.push_back(component);
				}
				}
			else {
				delete mesh;
			}
		}

		aiReleaseImport(scene);
		return meshGO;
	}

}

GameObject* ModuleLoadFBX::PrimitivesObjects(int Case)
{
	//draw Primitives
	GameObject* child;
	switch (Case)
	{
	case 1:
		if (App->imguiwindows->Selected == nullptr)
		{
			child = new GameObject(App->imguiwindows->RootGO);
		}

		else if (App->imguiwindows->Selected != nullptr)
		{
			child = new GameObject(App->imguiwindows->Selected);
		}
		break;
	case 2:
		MeshObject = LoadFile("Assets/Primitives/cube2.fbx", "Cube");
		break;
	case 3:
		MeshObject = LoadFile("Assets/Primitives/Plane.fbx", "Plane");
		break;
	case 4:
		MeshObject = LoadFile("Assets/Primitives/Pyramid.fbx", "Pyramid");
		break;
	case 5:
		MeshObject = LoadFile("Assets/Primitives/Sphere.fbx", "Sphere");
		break;
	case 6:
		MeshObject = LoadFile("Assets/Primitives/Cylinder.fbx", "Cylinder");
		break;
	}
	return nullptr;
}




void ModuleLoadFBX::LoadMesh(MyMesh* mesh) {


	glGenBuffers(1, (GLuint*)&(mesh->id_vertices));
	glGenBuffers(1, (GLuint*)&(mesh->id_indices));


	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertices * 3, mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);

	meshes.push_back(mesh);

	
}

update_status ModuleLoadFBX::PostUpdate(float dt)
{

		for (int i = 0; i < meshes.size(); i++) {

		if (App->imguiwindows->Wireframe == true) {
				//Wireframe Mode
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glLineWidth(2);
			}
				if (i < 2 && FBX1 == true)
			{

				meshes[i]->Render();
			}
			
			if (i >= 2 && i <= 2&& FBX2 == true)
			{
				meshes[i]->Render();
			}
			
			if (i >= 3 && FBX3 == true)
			{
				meshes[i]->Render();
			}
		}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return UPDATE_CONTINUE;
}
bool ModuleLoadFBX::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
		meshes[i] = nullptr;
	}
	meshes.clear();
	aiDetachAllLogStreams();
	return true;
}