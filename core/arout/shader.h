#pragma once

#include "../ew/external/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace arout {
	class Shader {
		//program ID
		unsigned int id;

	public:
		// constructor
		Shader(const char* vertexPath, const char* fragmentPath);

		//use/activate shader
		void use();

		//utility uniform functions
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
	};
}