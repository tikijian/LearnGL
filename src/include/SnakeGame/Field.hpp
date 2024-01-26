#ifndef FIELD_HPP
#define FIELD_HPP

#include "../Utils.h"
#include "../GlDeps.hpp"
#include "../GameObject.hpp"
#include "../Primitives.hpp"
#include "../ShaderProgram.hpp"

#include <string>
#include <iostream>

// const unsigned int TILE_W = 32;
// const unsigned int TILE_H = 32;

class Field : public GameObject {
private:
    unsigned int ebo;
    float cols;
    float rows;
    ShaderProgram * shader;
public:

    Field(float _cols, float _rows) : cols(_cols), rows(_rows)
    {
        modelTransform = glm::mat4(1.0f);
        position = glm::vec3(.0f);
    }
    ~Field(){}

    void initialize()
    {
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);
        
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(PLANE_VERTICES_DATA), PLANE_VERTICES_DATA, GL_STATIC_DRAW);
        
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // vertex positions
        auto stride = (COMPONENTS_PER_VERTEX_ATTRIBUTE + COMPONENTS_PER_TEXTURE_ATTRIBUTE) * sizeof(float);
        glVertexAttribPointer(0, COMPONENTS_PER_VERTEX_ATTRIBUTE, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(SHADER_VERTEX_ATTRIB_LOCATION);
        // texture coords
        const GLvoid* textureDataOffset = (void*)(COMPONENTS_PER_VERTEX_ATTRIBUTE * sizeof(float)); 
        glVertexAttribPointer(1, COMPONENTS_PER_TEXTURE_ATTRIBUTE, GL_FLOAT, GL_FALSE, stride, textureDataOffset);
        glEnableVertexAttribArray(SHADER_TEXTURE_ATTRIB_LOCATION);

        texture = loadTexture("snake-floor.png");

        // field position is fixed, so set it during init
        // auto fieldScale = (cols * rows) * SCALE_FACTOR;
        modelTransform = glm::scale(modelTransform, glm::vec3(3.0f));
        modelTransform = glm::translate(modelTransform, position);
        modelTransform = glm::rotate(modelTransform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
    }
    void update(){}

    void render()
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vao);
        shader->setMat4("model", modelTransform);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void setShader(ShaderProgram * shader)
    {
        this->shader = shader;
    }

    void cleanup()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
};

#endif