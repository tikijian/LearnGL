#include "../include/Primitives.hpp"
#include "../include/SnakeGame.hpp"

static const float Y_OFFSET = 1.0f;
static const int COLS = 20;
static const int ROWS = 15;

SnakeGame::SnakeGame(ShaderProgram * shaderProgram) :
    field {static_cast<float>(COLS), static_cast<float>(ROWS)}
{
    shader = shaderProgram;
    field.setShader(shader);
    baseMatrix = glm::mat4(1.0f);
    baseMatrix = glm::scale(baseMatrix, glm::vec3(SCALE_FACTOR));
    
    snake.xPos = 10;
    snake.yPos = 10;
    snake.direction = Directions::Up;

    blocks = std::vector {
        SnakeBlock {snake.xPos, snake.yPos+1, Directions::Up },
        SnakeBlock {snake.xPos, snake.yPos+2, Directions::Up },
        SnakeBlock {snake.xPos, snake.yPos+3, Directions::Up },
    };
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::initialize()
{
    field.initialize();

    cube = loadMesh(CUBE_VERTICES_DATA, "container.jpg");
}

void SnakeGame::cleanup() {
    field.cleanup();
}

void SnakeGame::render()
{
    field.render();

    glm::mat4 snakeMatrix = glm::translate(baseMatrix, glm::vec3((float)snake.xPos -10.0f, Y_OFFSET, (float)snake.yPos - 10.0f));
    shader->setMat4("model", snakeMatrix);
    renderMesh(cube, CUBE_TRIANGLES_COUNT);

    int count = blocks.size();
    for(int i = 0; i < count; i++)
    {
        // std::cout << blocks[i].xPos * SCALE_FACTOR << std::endl;
        glm::mat4 blockMatrix = glm::translate(baseMatrix, glm::vec3((float)blocks[i].xPos -10.0f, Y_OFFSET, (float)blocks[i].yPos - 10.0f));
        shader->setMat4("model", blockMatrix);
        renderMesh(cube, CUBE_TRIANGLES_COUNT);
    }

}
