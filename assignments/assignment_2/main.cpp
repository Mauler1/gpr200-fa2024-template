#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <arout/shader.cpp>
#include <arout/texture2D.cpp>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	//X		Y		Z		R		G	B		A		tex coords
	-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // bottom left
	 1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,	// bottom right
	 1.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 1.0f, // top right
	-1.0f,	1.0f, 0.0f,		1.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f	// top left
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};


const char* characterVertexShaderSource = "assets/characterVertexShader.vert";

const char* characterFragmentShaderSource = "assets/characterFragmentShader.frag";

const char* bgVertexShaderSource = "assets/bgVertexShader.vert";

const char* bgFragmentShaderSource = "assets/bgFragmentShader.frag";

const char* bgImageSource = "assets/winebrennerWall.jpg";

const char* fgImageSource = "assets/graphicWineWall.png";



int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!

	arout::Shader CharacterShader(characterVertexShaderSource, characterFragmentShaderSource);
	arout::Texture2D characterImage(fgImageSource, GL_NEAREST, GL_REPEAT, 0);
	arout::Shader BGShader(bgVertexShaderSource, bgFragmentShaderSource);
	//arout::Texture2D bgImage(bgImageSource, GL_NEAREST, GL_REPEAT, 0);
	//	^^ problem with this guy >:(

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	quad buffer
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//	XYZ position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// RGBA color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(1);

	//	quad location
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(sizeof(float)*7));
    glEnableVertexAttribArray(2);


	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float time = (float)glfwGetTime();

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		BGShader.use();
		BGShader.setFloat("uTime", time);
		//bgImage.bind();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		CharacterShader.use();

		//set time uniform
		CharacterShader.setFloat("uTime", time);

		// bind texture
		characterImage.bind();
		glBindVertexArray(VAO);

		//draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
