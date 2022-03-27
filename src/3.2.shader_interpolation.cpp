#if 0

#include <fstream>
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: check if glad is really needed??
//#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

// settings.
const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "Hellow Triangle";

void framebuffer_size_callback(GLFWwindow *win, int width, int height);
void processInput(GLFWwindow *win);
unsigned int createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   vertexColor = aColor;\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 vertexColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(vertexColor, 1.0f);\n"
                                   "}\n\0";

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

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init GLEW " << std::endl;
        return -1;
    }

// TODO: check if glad is really needed on macos ??
#if 0
    // glad: load all opengl function pointers.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // set up vertex data (and buffers) and configure vertex attributes.
    float vertices[] = {
        0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top-right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom-right
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom-left
    };
    unsigned int indicesFirst[] = {
        0, 1, 2, // first triangle
    };

    unsigned int vbo; // vertex buffer object
    unsigned int vao; // vertex array object
    unsigned int ebo; // element buffer object
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind the vertex array object first, then bind and set vertex buffers,
    // and then configure vertex attributes.
    glBindVertexArray(vao);

    // 0. copy our vertices array in a buffer for openGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesFirst), indicesFirst, GL_STATIC_DRAW);

    // 1. then set the vertex attributes pointers
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    unsigned int aColorAtrributeLocation = glGetAttribLocation(shaderProgram, "aColor");
    glVertexAttribPointer(aColorAtrributeLocation, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(aColorAtrributeLocation);
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw a triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events(keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

/**
 * @brief Create a Shader Program object
 *
 * @param vertexShaderSource    vertex shader source
 * @param fragmentShaderSource  fragment shader source.
 * @return unsigned int         shader program id on success, -1 on fail.
 */
unsigned int createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    if (vertexShaderSource == nullptr || fragmentShaderSource == nullptr)
    {
        std::cout << "ERROR:: vertex/fragment shader source is nullptr" << std::endl;
        return -1; // TODO: this is bad
    }
    // build and compile our shader program.
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile error.
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == false)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIED\n"
                  << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile error.
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == false)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FALIED\n"
                  << infoLog << std::endl;
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == false)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

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
void processInput(GLFWwindow *win)
{
    if (glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, true);
    }
}

#endif