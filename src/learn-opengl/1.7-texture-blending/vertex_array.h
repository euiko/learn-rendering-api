#ifndef LEARNOPENGL_VERTEXARRAY_H
#define LEARNOPENGL_VERTEXARRAY_H

#include <vector>
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
private:
    unsigned int m_id;
public:
    VertexArray();
    ~VertexArray();
    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) const;
};

#endif // !LEARNOPENGL_VERTEXARRAY_H