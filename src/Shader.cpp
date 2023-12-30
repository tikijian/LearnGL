#include "include/Shader.hpp"
#include "../vendor/glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* filepath, unsigned int shaderType)
{
    this->filepath = filepath;
    this->id = glCreateShader(shaderType);
}

Shader::~Shader()
{
}

bool Shader::compile()
{
    std::ifstream file;
    file.open(filepath);

    if (!file.is_open()) {
        std::cout << "Unable to open shader file!" << std::endl;
        exit(1);
    }

    std::stringstream strStream;
    strStream << file.rdbuf();
    std::string shaderSource = strStream.str();
    auto rawShaderSource = shaderSource.c_str();

    file.close();

    glShaderSource(id, 1, &rawShaderSource, NULL);
    glCompileShader(id);

    return true;
}

void Shader::del()
{
    glDeleteShader(id);
}