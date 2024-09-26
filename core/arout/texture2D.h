#pragma once

#include "../ew/external/glad.h"
#include "../ew/external/stb_image.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace arout {
	class Texture2D {
		unsigned int textureID;

	public:
		Texture2D(const char* texturePath);

		void use();
	};
}