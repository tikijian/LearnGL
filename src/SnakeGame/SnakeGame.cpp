#include "../include/Primitives.hpp"
#include "../include/SnakeGame.hpp"


SnakeGame::SnakeGame(ShaderProgram * shaderProgram)
{
    shader = shaderProgram;
    field.setShader(shader);
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::initialize()
{
    field.position = glm::vec3(.0f, -0.3f, -0.5f);
    // field.position = glm::vec3(.0f, .0f, .0f);
    field.initialize();
}

void SnakeGame::cleanup() {
    field.cleanup();
}

void SnakeGame::render()
{
    field.render();
}
