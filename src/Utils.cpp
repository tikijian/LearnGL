#define STB_IMAGE_IMPLEMENTATION
#include "include/Utils.h"

void log(std::string &message)
{
    std::cout << message << std::endl;
}

GLuint loadTexture(const std::string & filename)
{
    GLuint textureId;
    // load texture
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int texWidth, texHeight, nrChannels;
    unsigned char *data = stbi_load(std::string("textures/").append(filename).c_str(), &texWidth, &texHeight, &nrChannels, 0);

    if (!data) {
        //log(std::string(std::string("Unable to open texture ") + filename));
        exit(1);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return textureId;
}
