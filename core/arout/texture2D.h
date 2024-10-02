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
		int m_width, m_height;

	public:
		Texture2D(const char* texturePath, int filterMode, int wrapMode, int format);

		void bind();
	};
}