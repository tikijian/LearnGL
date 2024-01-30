#ifndef MESH_HPP
#define MESH_HPP

#include "GlDeps.hpp"
#include <string>
#include <vector>

struct Mesh
{
    GLuint vbo;
    GLuint vao;
    GLuint texture;
};

const Mesh loadMesh(const std::vector<float> & bufferData);
void renderMesh(const Mesh & mesh, GLuint textureId, unsigned int trianglesCount);
void destroyMesh(Mesh & mesh);

#endif