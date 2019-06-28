#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

#define GLCall(x) glClearError();\
    x;\
    assert(glIsError(#x, __FILE__, __LINE__))

#ifndef RESOURCE_PATH
#define RESOURCE_PATH "res"
#endif

static void glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool glIsError(const char* function_call_string, const char* file, int line)
{
    while(GLenum errorCode = glGetError())
    {
        std::cout << "[ OPENGL ERROR ] => ( " << errorCode << " ) on function call "
            << function_call_string << " in file " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

struct ShaderSources
{
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderSources parseSource(const std::string& filePath)
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream is(filePath);
    std::string line;
    std::stringstream sourceStream[2];

    ShaderType type = ShaderType::NONE;
    while(getline(is, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            continue;
        }
        sourceStream[(int)type] << line << "\n";
    }
    return {sourceStream[0].str(), sourceStream[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string& source )
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    if(vs) glAttachShader(program, vs);
    if(fs) glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
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
        -0.5f, -0.5f, // 0
        0.5f, -0.5f, // 1
        0.5f, 0.5f, // 2
        -0.5f, 0.5f // 3
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 0, 3
    };
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    unsigned int indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderSources shaderSources = parseSource(RESOURCE_PATH "/shaders/basic.glsl");
    std::cout << "VERTEX\n";
    std::cout << shaderSources.vertexSource;
    std::cout << "FRAGMENT\n";
    std::cout << shaderSources.fragmentSource;
    unsigned int shader = createShader(shaderSources.vertexSource, shaderSources.fragmentSource);
    glUseProgram(shader);

    int u_Color = glGetUniformLocation(shader, "u_Color");
    float red = 0.0f;
    float inc = 0.5;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(u_Color, red, 0.5f, 0.8f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        if(red > 1.0f) inc = -0.05f;
        if(red < 0.0f) inc = 0.05f;
        red += inc;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
