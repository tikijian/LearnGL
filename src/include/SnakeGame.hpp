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
    GLuint containerTexId;
    GLuint baitTexId;
    GLuint headTexId;
    unsigned short size;
    glm::mat4 baseMatrix;
    SnakeBlock snake;
    SnakeBlock bait;
    std::vector<SnakeBlock> blocks;
    Mesh cube;
    Field field;
    ShaderProgram * shader;

    bool isBaitEaten();
    void updateSnakeBody();

public:
    SnakeGame(ShaderProgram * shaderProgram);
    ~SnakeGame();

    void initialize();
    void handleInput(GLFWwindow *window);
    void update();
    void render();

    void cleanup();
};
 
#endif