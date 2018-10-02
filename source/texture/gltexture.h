/* Created by David Klostermann on 02.10.2018. */
#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GLEW/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/common.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <sstream>
#include <fstream>

struct GLTextureException : public std::exception {
    std::string error;

    GLTextureException(std::string error){
        this->error = error;

    }

    std::string what(){
        return this->error;
    }
};

class GLTexture {
private:
    GLuint textureID;

    void createGLImage(glm::vec4* imageData, int width, int height, GLenum mode);
public:
    GLTexture(const char* filePath);
    ~GLTexture();

    void bind();
};


#endif
