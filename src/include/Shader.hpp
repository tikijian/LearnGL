#ifndef SHADER_HPP
#define SHADER_HPP

class Shader
{
private:
    const char* filepath;

    bool checkErrors();
public:
    unsigned int id;

    Shader(const char* filepath, unsigned int shaderType);
    ~Shader();

    bool compile();
    void del();
};

#endif