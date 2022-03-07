#if 0
#include <fstream>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

const GLuint DEFAULT_WINDOW_WIDTH = 800, DEFAULT_WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "OpenGL Application";


int main()
{
     GLFWwindow* window;

    if (!glfwInit())
        exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        exit(1);



    glClearColor(1.0f, 0.1f, 0.1f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //shader->use();
       // cube->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit(0);
}  


#endif