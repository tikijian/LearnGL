#include "../include/Primitives.hpp"
#include "../include/SnakeGame.hpp"
#include <cstdlib>
#include <ctime>

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
    
    std::srand(std::time(nullptr));
    bait.xPos = std::rand() % COLS;
    bait.xPos = std::rand() % ROWS;
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::initialize()
{
    field.initialize();

    cube = loadMesh(CUBE_VERTICES_DATA);
    containerTexId = loadTexture("crate.png", GL_RGBA);
    headTexId = loadTexture("awesomeface.png", GL_RGBA);
    baitTexId = loadTexture("bait.jpg");
}

void SnakeGame::cleanup()
{
    field.cleanup();
    destroyMesh(cube);
}

void SnakeGame::update()
{
    for (int i = blocks.size() - 1; i >= 1; i--) {
        blocks[i].xPos = blocks[i-1].xPos;
        blocks[i].yPos = blocks[i-1].yPos;
        blocks[i].direction = blocks[i-1].direction;
    }
    
    blocks[0].xPos = snake.xPos;
    blocks[0].yPos = snake.yPos;
    blocks[0].direction = snake.direction;
    
    switch (snake.direction) {
        case Directions::Up:
            snake.yPos -= 1;
            break;
        case Directions::Down:
            snake.yPos += 1;
            break;
        case Directions::Left:
            snake.xPos -= 1;
            break;
        case Directions::Right:
            snake.xPos += 1;
            break;
        default:
            break;
    }
    
    if(snake.xPos > COLS)
        snake.xPos = 0;
    else if(snake.xPos < 0)
        snake.xPos = COLS;
    
    if(snake.yPos > ROWS)
        snake.yPos = 0;
    else if (snake.yPos < 0)
        snake.yPos = ROWS;

}

void SnakeGame::render()
{
    field.render();

    glm::mat4 snakeMatrix = glm::translate(baseMatrix, glm::vec3((float)snake.xPos -10.0f, Y_OFFSET, (float)snake.yPos - 10.0f));
    shader->setMat4("model", snakeMatrix);
    renderMesh(cube, headTexId, CUBE_TRIANGLES_COUNT);

    int count = blocks.size();
    for(int i = 0; i < count; i++)
    {
        glm::mat4 blockMatrix = glm::translate(baseMatrix, glm::vec3((float)blocks[i].xPos -10.0f, Y_OFFSET, (float)blocks[i].yPos - 10.0f));
        shader->setMat4("model", blockMatrix);
        renderMesh(cube, containerTexId, CUBE_TRIANGLES_COUNT);
    }

    glm::mat4 baitMatrix = glm::translate(baseMatrix, glm::vec3((float)bait.xPos -10.0f, Y_OFFSET, (float)bait.yPos - 10.0f));
    shader->setMat4("model", baitMatrix);
    renderMesh(cube, baitTexId, CUBE_TRIANGLES_COUNT);
    
    updateSnakeBody();
}

bool SnakeGame::isBaitEaten()
{
    return snake.xPos == bait.xPos && snake.yPos == bait.yPos;
}

void SnakeGame::updateSnakeBody()
{
    if(! isBaitEaten() ) return;

    // generate new Bait
    bait.xPos = rand() % COLS;
    bait.yPos = rand() % ROWS;
    
    // add new block to the end of snake body
    int last = blocks.size() - 1;
    SnakeBlock newBlock { blocks[last].xPos, blocks[last].yPos, blocks[last].direction };
    
    // calculate correct coordinates offset, depending on direction
    if (newBlock.direction == Directions::Up || newBlock.direction == Directions::Left) {
        newBlock.yPos += 1;
    } else {
        newBlock.yPos -= 1;
    }

    blocks.push_back(newBlock);
}

void SnakeGame::handleInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        snake.direction = Directions::Down;
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        snake.direction = Directions::Up;
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        snake.direction = Directions::Left;
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        snake.direction = Directions::Right;
}