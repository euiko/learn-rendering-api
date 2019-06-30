#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "shader.h"
#include "texture.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << RESOURCE_PATH << std::endl;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        std::cout << "Error while initializing glew with errors: " << glewGetErrorString(err);
        return err;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f, -0.5f, 1.0f, 0.0f, // 1
        0.5f, 0.5f, 1.0f, 1.0f, // 2
        -0.5f, 0.5f, 0.0f, 1.0f // 3
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    Renderer renderer;

    VertexArray va;

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
    
    IndexBuffer ib(indices, 6);
    
    Shader shader("shaders/texture2d.glsl");
    Texture texture("textures/logo.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);

    float red = 0.0f;
    float inc = 0.5;
    shader.unbind();
    vb.unbind();
    va.unbind();
    ib.unbind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
    
        shader.bind();
        // shader.setUniform4f("u_Color", red, 0.4f, 0.8f, 1.0f);

        renderer.draw(va, ib, shader);

        if(red > 1.0f) inc = -0.05f;
        if(red < 0.0f) inc = 0.05f;
        red += inc;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
