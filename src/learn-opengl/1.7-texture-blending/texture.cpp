#include "texture.h"
#include "renderer.h"
#include <GL/glew.h>
#include <stb_image.h>

Texture::Texture(const std::string& filepath) 
    : m_filepath(filepath), m_width(0), m_height(0), m_pixelBit(0), m_localBuffer(nullptr)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load((RESOURCE_PATH + filepath).c_str(), &m_width, &m_height, &m_pixelBit, 4);
    if(!m_localBuffer) std::cout << "Failed to load texture on " << filepath << std::endl;
    GLCall(glGenTextures(1, &m_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    unbind();

    if(m_localBuffer) stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_id));
}

void Texture::bind(unsigned int slot /*= 0 */) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::getWidth() const&
{
    return m_width;
}
int Texture::getHeight() const&
{
    return m_height;
}