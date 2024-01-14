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
    field.initialize();
}

void SnakeGame::cleanup() {
    field.cleanup();
}

void SnakeGame::render()
{
    field.render();
}
