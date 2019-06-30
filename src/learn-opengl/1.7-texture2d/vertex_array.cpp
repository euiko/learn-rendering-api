#include "vertex_array.h"
#include "renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_id));
}

void VertexArray::unbind() const 
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) const
{
    bind();
    buffer.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];   
        GLCall(glEnableVertexAttribArray(i));
        // std::cout << i << " " << element.count << " " << element.type << " " << element.normalized << " " << layout.getStride() << " " << (const void*)offset << std::endl;
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}