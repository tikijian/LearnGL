#ifndef UTILS_H
#define UTILS_H

#include "../../vendor/stb_image.h"
#include "GlDeps.hpp"

#include <iostream>
#include <string>

void log(std::string & message);
GLuint loadTexture(const std::string & filename, GLuint colorFormat = GL_RGB);
#endif
