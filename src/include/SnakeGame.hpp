#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "GlDeps.hpp"
#include "GameObject.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Primitives.hpp"
#include <iostream>
#include <vector>
#include "SnakeGame/Field.hpp"

// directions
enum Directions {
    Up = 0,
    Down,
    Left,
    Right
};

struct SnakeBlock {
    int xPos;
    int yPos;
    Directions direction;
};

// Constants
class SnakeGame
{
private:
    Field field;
    Mesh cube;
    ShaderProgram * shader;
    SnakeBlock snake;
    glm::mat4 baseMatrix;
    std::vector<SnakeBlock> blocks;
    unsigned short size;
public:
    SnakeGame(ShaderProgram * shaderProgram);
    ~SnakeGame();

    void initialize();
    void handleInput();
    void update();
    void render();

    void cleanup();
};
 
#endif