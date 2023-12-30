#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "Shader.hpp"

class ShaderProgram
{
private:
    unsigned int id;
public:
    ShaderProgram(const Shader * vertexShdr, const Shader * fragmentShdr);
    ~ShaderProgram();

    void use();
};

#endif