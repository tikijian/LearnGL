#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "GlDeps.hpp"
#include "GameObject.hpp"
#include "ShaderProgram.hpp"
#include <iostream>
#include "SnakeGame/Field.hpp"

// directions
enum Directions {
    Up = 0,
    Down,
    Left,
    Right
};

// Constants
const unsigned int TILE_W = 32;
const unsigned int TILE_H = 32;

const unsigned int FIELD_W = 20;
const unsigned int FIELD_H = 15;

class SnakeGame
{
private:
    Field field;
    ShaderProgram * shader;
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