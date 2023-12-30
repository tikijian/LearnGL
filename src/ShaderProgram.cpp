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