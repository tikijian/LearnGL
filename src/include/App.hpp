#ifndef APP_HPP
#define APP_HPP

#include "GlDeps.hpp"

class App
{
private:
public:
    static const unsigned int SCR_WIDTH = 1024;
    static const unsigned int SCR_HEIGHT = 768;
    
    GLFWwindow * window;

    App();
    ~App();
    
    void terminate();
    bool shouldClose();
    void swapBuffers();

    GLFWwindow* initialize();
};


#endif