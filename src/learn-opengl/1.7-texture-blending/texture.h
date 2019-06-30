#ifndef LEARNOPENGL_TEXTURE_H
#define LEARNOPENGL_TEXTURE_H
#include <iostream>

class Texture
{
private:
    unsigned int m_id;
    std::string m_filepath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_pixelBit;
public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
    
    int getWidth() const&;
    int getHeight() const&;
};

#endif // !LEARNOPENGL_TEXTURE_H