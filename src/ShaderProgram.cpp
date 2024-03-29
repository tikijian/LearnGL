#include "include/GlDeps.hpp"
#include "include/ShaderProgram.hpp"
#include <iostream>

ShaderProgram::ShaderProgram(const Shader & vertexShdr, const Shader & fragmentShdr)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShdr.id);
    glAttachShader(id, fragmentShdr.id);
    glLinkProgram(id);
    checkErrors();
    vertexShdr.del();
    fragmentShdr.del();
}

ShaderProgram::ShaderProgram(const char * vertexShdrPath, const char * fragmentShdrPath)
{
    Shader vertexShdr(vertexShdrPath, GL_VERTEX_SHADER);
    vertexShdr.compile();
    Shader fragmentShdr(fragmentShdrPath, GL_FRAGMENT_SHADER);
    fragmentShdr.compile();

    id = glCreateProgram();
    glAttachShader(id, vertexShdr.id);
    glAttachShader(id, fragmentShdr.id);
    glLinkProgram(id);
    checkErrors();

    vertexShdr.del();
    fragmentShdr.del();
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::use()
{
    glUseProgram(id);
}

bool ShaderProgram::checkErrors()
{
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
     
    return (bool)success;
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}

void ShaderProgram::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::setMat4(const std::string &name, glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
void ShaderProgram::setVec3(const std::string &name, float v1, float v2, float v3)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}
