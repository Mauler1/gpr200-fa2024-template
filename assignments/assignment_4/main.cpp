#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <arout/shader.cpp>
#include <arout/texture2D.cpp>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float fov = 60.0f;


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f)),
        glm::vec3(ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f),  ew::RandomRange(-15.0f, 15.0f))
        //oh beloved professor eric winebrenner do not kill me for not using a loop
};

glm::mat4 scale(float x, float y, float z) {
    return glm::mat4(
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}
glm::mat4 rotateZ(float a) {
    glm::mat4 m;
    m[0][0] = cos(a);
    m[1][0] = -sin(a);
    m[0][1] = sin(a);
    m[1][1] = cos(a);
    m[2][2] = 1;
    m[3][3] = 1;
    return m;
}

glm::mat4 translate(float x, float y, float z) {
    glm::mat4 m = glm::mat4(1); //identity matrix
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
    return m;
}

void processInput(GLFWwindow* window)
{
    //escape program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //cam movement
    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * 2.0f * cameraFront;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 120.0f)
        fov = 120.0f;
}

const char* vertexShaderSource = "assets/vertexShader.vert";

const char* fragmentShaderSource = "assets/fragmentShader.frag";

const char* lightVertexSource = "assets/lightVertShader.vert";

const char* lightFragmentSource = "assets/lightFragShader.frag";

const char* cubeImageSource = "assets/freakbob.png";



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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD Failed to load GL headers");
        return 1;
    }
    //Initialization goes here!

    arout::Shader cubeShader(vertexShaderSource, fragmentShaderSource);
    arout::Texture2D cubeImage(cubeImageSource, GL_NEAREST, GL_REPEAT, GL_RGB);

    //mouse capture
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //	XYZ position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // TEX coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float time = (float)glfwGetTime();

        //Clear framebuffer
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeImage.bind();
        cubeShader.use();

        //projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
        cubeShader.setMat4("_Projection", projection);

        //set time uniform
        cubeShader.setFloat("uTime", time);

        //view matrix
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        cubeShader.setMat4("_View", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 20; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = scale((sin(deltaTime) + 1.5f) / 5.0f, (cos(deltaTime) + 1.5f) / 5.0f, (sin(deltaTime) + 1.5f) / 5.0f) * model;
            model = glm::rotate(model, (deltaTime + 1) / deltaTime * glm::radians(20.0f * (i + 1.0f)), glm::vec3(1.0f, 0.3f, 0.5f));
            //model = translate(cosf(time)/5.0f, sinf(time)/5.0f, 0.0f) * model;
            cubeShader.setMat4("_Model", model);

            //draw call
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //Drawing happens here!
        glfwSwapBuffers(window);
    }
    printf("Shutting down...");
}