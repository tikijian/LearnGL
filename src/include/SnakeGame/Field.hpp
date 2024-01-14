#ifndef FIELD_HPP
# define FIELD_HPP

#include "../GlDeps.hpp"
#include "../GameObject.hpp"
#include "../Primitives.hpp"
#include "../ShaderProgram.hpp"

class Field : public GameObject {
private:
    unsigned int ebo;
    ShaderProgram * shader;
public:

    Field()
    {
        modelTransform = glm::mat4(1.0f);
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
        glVertexAttribPointer(0, COMPONENTS_PER_VERTEX_ATTRIBUTE, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(SHADER_VERTEX_ATTRIB_LOCATION);
        // texture coords:
        const GLvoid* textureDataOffset = (void*)(COMPONENTS_PER_VERTEX_ATTRIBUTE * sizeof(float)); 
        glVertexAttribPointer(1, COMPONENTS_PER_TEXTURE_ATTRIBUTE, GL_FLOAT, GL_FALSE, 5 * sizeof(float), textureDataOffset);
        glEnableVertexAttribArray(SHADER_TEXTURE_ATTRIB_LOCATION);
    }
    void update(){}

    void render()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(.0f, -1.2f, -1.5f));
        model = glm::scale(model, glm::vec3(10.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
        shader->setMat4("model", model);
        glBindVertexArray(vao);
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