#include "vertex_buffer_layout.h"
#include <cassert>

VertexBufferLayout::VertexBufferLayout()
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}


std::vector<VertexBufferElement> VertexBufferLayout::getElements() const&
{
    return m_elements;
}
unsigned int VertexBufferLayout::getStride() const
{
    return m_stride;
}

template <typename T>
void VertexBufferLayout::push(unsigned int count)
{
    assert(false);
}

template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
    m_elements.push_back({GL_FLOAT, count, false});
    m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::push<int>(unsigned int count)
{
    m_elements.push_back({GL_INT, count, false});
    m_stride += VertexBufferElement::getSizeOfType(GL_INT) * count;
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_INT, count, false});
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::push<char>(unsigned int count)
{
    m_elements.push_back({GL_BYTE, count, false});
    m_stride += VertexBufferElement::getSizeOfType(GL_BYTE) * count;
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_BYTE, count, false});
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}