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

void Renderer::draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const
{
    vertex_array.bind();
    index_buffer.bind();
    shader.bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}