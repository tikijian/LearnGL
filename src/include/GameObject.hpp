#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
protected:
    unsigned int vbo;
    unsigned int vao;

public:
    glm::vec3 position;
    glm::mat4 modelTransform;

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif
