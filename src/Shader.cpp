#include "include/GlDeps.hpp"
#include "include/Shader.hpp"
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
    return checkErrors();
}

void Shader::del() const
{
    glDeleteShader(id);
}

bool Shader::checkErrors()
{
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return (bool)success;
}