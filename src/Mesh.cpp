#include "include/Utils.h"
#include "include/Mesh.hpp"

const Mesh loadMesh(const std::vector<float> & bufferData, const char * filename)
{
    Mesh mesh { 0, 0, 0 };
    glGenBuffers(1, &mesh.vbo);
    glGenVertexArrays(1, &mesh.vao);

    // data
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), bufferData.data(), GL_STATIC_DRAW);

    glBindVertexArray(mesh.vao);
    auto stride = (COMPONENTS_PER_VERTEX_ATTRIBUTE + COMPONENTS_PER_TEXTURE_ATTRIBUTE) * sizeof(float);
    // vertex positions
    glVertexAttribPointer(0, COMPONENTS_PER_VERTEX_ATTRIBUTE, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(SHADER_VERTEX_ATTRIB_LOCATION);
    // texture coords:
    const GLvoid* textureDataOffset = (void*)(COMPONENTS_PER_VERTEX_ATTRIBUTE * sizeof(float)); 
    glVertexAttribPointer(1, COMPONENTS_PER_TEXTURE_ATTRIBUTE, GL_FLOAT, GL_FALSE, stride, textureDataOffset);
    glEnableVertexAttribArray(SHADER_TEXTURE_ATTRIB_LOCATION);

    mesh.texture = loadTexture(filename);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return mesh;
}

void renderMesh(const Mesh &mesh, unsigned int trianglesCount)
{
    glBindVertexArray(mesh.vao);
    glBindTexture(GL_TEXTURE_2D, mesh.texture);
    glDrawArrays(GL_TRIANGLES, 0, trianglesCount);
}

void destroyMesh(Mesh &mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vao);
}
