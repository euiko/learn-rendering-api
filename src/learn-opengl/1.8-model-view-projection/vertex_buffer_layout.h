#ifndef LEARNOPENGL_VERTEXBUFFERLAYOUT_H
#define LEARNOPENGL_VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_INT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_BYTE: return 1;
        case GL_UNSIGNED_BYTE: return 1;
        default: return 0;
        }
    }
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();
    std::vector<VertexBufferElement> getElements() const&;
    unsigned int getStride() const;
    template <typename T>
    void push(unsigned int count);
};


#endif // !LEARNOPENGL_VERTEXBUFFERLAYOUT_H