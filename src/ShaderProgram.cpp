#include "include/ShaderProgram.hpp"
#include "../vendor/glad/glad.h"
#include <iostream>

ShaderProgram::ShaderProgram(const Shader * vertexShdr, const Shader * fragmentShdr)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShdr->id);
    glAttachShader(id, fragmentShdr->id);
    glLinkProgram(id);
    checkErrors();
    vertexShdr->del();
    fragmentShdr->del();
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