#ifndef LEARNOPENGL_INDEXBUFFER_H
#define LEARNOPENGL_INDEXBUFFER_H

class IndexBuffer
{
private:
    unsigned int m_id;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
};

#endif // !LEARNOPENGL_INDEXBUFFER_H