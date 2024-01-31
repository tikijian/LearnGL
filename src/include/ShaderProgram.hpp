#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

class ShaderProgram
{
private:
    bool checkErrors();
public:
    unsigned int id;

    ShaderProgram(const Shader & vertexShdr, const Shader & fragmentShdr);
    ShaderProgram(const char * vertexShdrPath, const char * fragmentShdrPath);
    ~ShaderProgram();

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 &matrix);
    void setVec3(const std::string &name, float v1, float v2, float v3);
};

#endif