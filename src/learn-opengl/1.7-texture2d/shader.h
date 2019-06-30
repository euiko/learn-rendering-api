#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <iostream>

struct ShaderSources
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    unsigned int m_id;
public:
    Shader(const std::string& filepath);
    ~Shader();
    
    void bind() const;
    void unbind() const;
    void setUniform4f(const std::string& filepath, float v1, float v2, float v3, float v4) const;
private:    
    int getUniformLocation(const std::string& name) const;
    ShaderSources parseSource(const std::string& filePath) const;
    unsigned int compileShader(unsigned int type, const std::string& source) const;
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) const;
};


#endif // !LEARNOPENGL_SHADER_H