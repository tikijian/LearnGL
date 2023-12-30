#include "include/ShaderProgram.hpp"
#include "../vendor/glad/glad.h"

ShaderProgram::ShaderProgram(const Shader * vertexShdr, const Shader * fragmentShdr)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShdr->id);
    glAttachShader(id, fragmentShdr->id);
    glLinkProgram(id);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::use()
{
    glUseProgram(id);
}