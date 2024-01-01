#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>
#include "Shader.hpp"

class ShaderProgram
{
private:
    bool checkErrors();
public:
    unsigned int id;

    ShaderProgram(const Shader * vertexShdr, const Shader * fragmentShdr);
    ShaderProgram(const char * vertexShdrPath, const char * fragmentShdrPath);
    ~ShaderProgram();

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif