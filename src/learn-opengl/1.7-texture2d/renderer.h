#ifndef LEARNOPENGL_RENDERER_H
#define LEARNOPENGL_RENDERER_H

#include <GL/glew.h>
#include <cassert>
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

#define GLCall(x) glClearError();\
    x;\
    assert(glIsError(#x, __FILE__, __LINE__))

#ifndef RESOURCE_PATH
#define RESOURCE_PATH "res/"
#endif

void glClearError();

bool glIsError(const char* function_call_string, const char* file, int line);

class Renderer
{
private:
    /* data */
public:
    Renderer(/* args */);
    ~Renderer();

    void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const Shader& shader) const;
    void clear() const;
};

#endif // !LEARNOPENGL_RENDERER_H