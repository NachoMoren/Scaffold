#pragma once

#include "Globals.h"
#include <vector>

#include "DevIL/include/ilut.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/il.h"

#pragma comment(lib, "Devil/libx86/DevIL.lib")
#pragma comment(lib, "Devil/libx86/ILU.lib")
#pragma comment(lib, "Devil/libx86/ILUT.lib")

class TextureImporter {
public:
	GLuint ImportTexture(const char* filePath);
	void InitDevil(); 

	GLuint textureID, width, heigth; 
};