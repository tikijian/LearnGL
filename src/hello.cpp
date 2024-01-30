#include "include/GlDeps.hpp"

#include <iostream>
#include <math.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/Utils.h"
#include "include/App.hpp"
#include "include/Shader.hpp"
#include "include/ShaderProgram.hpp"
#include "include/Camera.hpp"

#include "include/Primitives.hpp"
#include "include/SnakeGame.hpp"
#include "include/Mesh.hpp"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);


// settings
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// camera
Camera camera(glm::vec3(0.0f, 2.3f, 3.0f));
float lastX;
float lastY;
bool firstMouse = true;

int main()
{
    App app;
    app.initialize();

    glfwSetCursorPosCallback(app.window, mouse_callback);

    lastX = app.SCR_WIDTH / 2.0f;
    lastY = app.SCR_HEIGHT / 2.0f;

    ShaderProgram shProgram("shaders/vBasic.glsl", "shaders/fBasic.glsl");
    shProgram.use();

    // projection
    glm::mat4 projection;
    float ratio = static_cast<float>(App::SCR_WIDTH) / static_cast<float>(App::SCR_HEIGHT);
    projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
    shProgram.setMat4("projection", projection);

    SnakeGame game(&shProgram);
    game.initialize();

    // Mesh cube1 = loadMesh(CUBE_VERTICES_DATA, "container.jpg");
    // Mesh cube2 = loadMesh(CUBE_VERTICES_DATA, "container.jpg");
    
    int fps = 0;
    float timer = .0f;
    while (!app.shouldClose())
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        timer += deltaTime;
        lastFrame = currentFrame;

        // input
        processInput(app.window);
        game.handleInput(app.window);
        
        if (timer > .4f) {
            glfwSetWindowTitle(app.window, std::to_string(fps).c_str());
            timer = 0.0f;
            fps = 0.0;

            game.update();
        }


        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // view
        glm::mat4 view = camera.GetViewMatrix();
        shProgram.setMat4("view", view);

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(2.0f, .0f, .0f));
        // shProgram.setMat4("model", model);

        // renderMesh(cube1, CUBE_TRIANGLES_COUNT);

        // model
        // glm::mat4 model(1.0f);
        // model = glm::scale(model, glm::vec3(0.5f));
        // model = glm::translate(model, glm::vec3(1.0f, 1.0f, 3.0f));
        // model = glm::translate(model, glm::vec3(-2.0f, .7f, -2.0f));
        // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // model = glm::rotate(model, currentFrame * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // shProgram.setMat4("model", model);

        // renderMesh(cube1, CUBE_TRIANGLES_COUNT);
        
        // model = glm::translate(model, glm::vec3(1.0f, 1.0f, .0f));
        // shProgram.setMat4("model", model);
        // renderMesh(cube1, CUBE_TRIANGLES_COUNT);
        
        // model = glm::translate(model, glm::vec3(1.0f, 1.0f, .0f));
        // shProgram.setMat4("model", model);
        // renderMesh(cube1, CUBE_TRIANGLES_COUNT);

        game.render();

        // transform = glm::mat4(1.0f); // reset it to identity matrix
        // transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        // transform = glm::scale(transform, glm::vec3(sin(timeValue)));
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        app.swapBuffers();

        fps++;
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // destroyMesh(cube1);
    // destroyMesh(cube2);
    game.cleanup();

    app.terminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
        glfwSwapInterval(0);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
