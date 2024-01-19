#ifndef SNAKE_HPP
# define SNAKE_HPP

#include "../Utils.h"
#include "../GlDeps.hpp"
#include "../GameObject.hpp"
#include "../Primitives.hpp"
#include "../ShaderProgram.hpp"

#include <string>
#include <iostream>

class Snake : public GameObject
{
private:
    /* data */
public:
    Snake(/* args */);
    ~Snake();
};

#endif