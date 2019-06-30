#include "shader.h"
#include "renderer.h"
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
{
    ShaderSources shaderSources = parseSource(RESOURCE_PATH + filepath);
    std::cout << "VERTEX\n";
    std::cout << shaderSources.vertexSource;
    std::cout << "FRAGMENT\n";
    std::cout << shaderSources.fragmentSource;
    GLCall(m_id = createShader(shaderSources.vertexSource, shaderSources.fragmentSource));
    bind();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_id));
}

void Shader::setUniform1i(const std::string& name, int value)
{
    bind();
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value)
{
    bind();
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    bind();
    GLCall(glUniform4f(getUniformLocation(name), v1, v2, v3, v4));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_id));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

// private section

int Shader::getUniformLocation (const std::string& name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    
    GLCall(int uniformLocation = glGetUniformLocation(m_id, name.c_str()));
    if(uniformLocation < 0)
    {
        std::cout << "[OPENGL] ERROR => " << "Uniform " << name << " not found in shader" << std::endl;
    }
    m_uniformLocationCache[name] = uniformLocation;
    return uniformLocation;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source ) const
{
    GLCall(unsigned int shader = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(shader, 1, &src, NULL));
    GLCall(glCompileShader(shader));

    int compiled;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
    if(!compiled)
    {
        int length;
        GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(shader, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(shader));
        return 0;
    }

    return shader;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) const
{
    GLCall(unsigned int program = glCreateProgram());
    GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));
    GLCall(if(vs) glAttachShader(program, vs));
    GLCall(if(fs) glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(if(vs) glDeleteShader(vs));
    GLCall(if(fs) glDeleteShader(fs));

    return program;
}

ShaderSources Shader::parseSource(const std::string& filePath) const
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream is(filePath);
    std::string line;
    std::stringstream sourceStream[2];

    ShaderType type = ShaderType::NONE;
    while(getline(is, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            continue;
        }
        sourceStream[(int)type] << line << "\n";
    }
    return {sourceStream[0].str(), sourceStream[1].str()};
}