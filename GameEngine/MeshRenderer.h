#pragma once

#include "Globals.h"
#include <vector>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "Glew/Include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

struct Mesh
{
	//Index
	uint idIndex = 0; // index in VRAM
	uint numIndex = 0;
	uint* index = nullptr;

	//Vertex
	uint idVertex = 0; // unique vertex in VRAM
	uint numVertex = 0;
	float* vertex = nullptr;

	uint textureID;


	uint VBO, EBO;
};

class MeshRenderer {
public:

	void LoadMesh(const char* filePath);

	void FillBuffers();

	void DrawMeshes();

	void DrawNormals();

private:

	std::vector<Mesh*> meshArray;
};
