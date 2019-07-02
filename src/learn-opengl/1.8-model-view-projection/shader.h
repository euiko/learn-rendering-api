#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderSources
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    unsigned int m_id;
    std::string m_filepath;
    std::unordered_map<std::string, int> m_uniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();
    
    void bind() const;
    void unbind() const;
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    int getUniformLocation(const std::string& name);
    ShaderSources parseSource(const std::string& filePath) const;
    unsigned int compileShader(unsigned int type, const std::string& source) const;
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) const;
};


#endif // !LEARNOPENGL_SHADER_H