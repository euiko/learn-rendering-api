#include "renderer.h"
#include <iostream>

void glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool glIsError(const char* function_call_string, const char* file, int line)
{
    while(GLenum errorCode = glGetError())
    {
        std::cout << "[ OPENGL ERROR ] => ( " << errorCode << " ) on function call "
            << function_call_string << " in file " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer(/* args */)
{
}

Renderer::~Renderer()
{
}