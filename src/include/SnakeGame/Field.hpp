#ifndef FIELD_HPP
# define FIELD_HPP

#include "../GlDeps.hpp"
#include "../GameObject.hpp"
#include "../Primitives.hpp"

class Field : public GameObject {
private:
    unsigned int ebo;
public:

    Field()
    {
        modelTransform = glm::mat4(1.0f);
    }
    ~Field(){}

    void initialize()
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(PLANE_VERTICES_DATA), PLANE_VERTICES_DATA, GL_STATIC_DRAW);
        
        glGenBuffers(1, &ebo);
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenBuffers(1, &vao);
        glBindVertexArray(vao);
        // vertex positions
        glVertexAttribPointer(0, COMPONENTS_PER_VERTEX_ATTRIBUTE, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        // texture coords:
        const GLvoid* textureDataOffset = (void*)(COMPONENTS_PER_VERTEX_ATTRIBUTE * sizeof(float)); 
        glVertexAttribPointer(1, COMPONENTS_PER_TEXTURE_ATTRIBUTE, GL_FLOAT, GL_FALSE, 5 * sizeof(float), textureDataOffset);

        // size and position
    }
    void update(){}

    void render()
    {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void cleanup()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
};

#endif