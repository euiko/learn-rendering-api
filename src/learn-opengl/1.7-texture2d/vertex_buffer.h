#ifndef LEARNOPENGL_VERTEXBUFFER_H
#define LEARNOPENGL_VERTEXBUFFER_H

class VertexBuffer
{
private:
    unsigned int m_id;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif // !LEARNOPENGL_VERTEXBUFFER_H