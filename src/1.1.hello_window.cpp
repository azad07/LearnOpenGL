#if 0

#include <fstream>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//TODO: check if glad is really needed??
//#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "Hellow Window";

/**
 * @brief whenever the window size changed (by OS or user resize) this callback function executes.
 * 
 * @param win   window handle
 * @param width widnow width
 * @param height window height
 */
void framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
    // make sure the viewport matches the new window dimensions.
    glViewport(0, 0, width, height);
}

/**
 * @brief process all input.
 * 
 * @param win  window handle. 
 */
void processInput(GLFWwindow *win){
    if(glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS){
        glfwSetWindowShouldClose(win, true);
    }
}

int main()
{
    // glfw: initialize and configure.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // glfw window creation.
    GLFWwindow *window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//TODO: check if glad is really needed on macos ??
#if 0
    // glad: load all opengl function pointers.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif

// render loop
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glfw: swap buffers and poll IO events(keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

#endif