#ifndef LEARNOPENGL_RENDERER_H
#define LEARNOPENGL_RENDERER_H

#include <GL/glew.h>
#include <cassert>

#define GLCall(x) glClearError();\
    x;\
    assert(glIsError(#x, __FILE__, __LINE__))

#ifndef RESOURCE_PATH
#define RESOURCE_PATH "res"
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
};

#endif // !LEARNOPENGL_RENDERER_H