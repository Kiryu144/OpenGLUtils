/* Created by David Klostermann on 02.10.2018. */
#include "gltexture.h"

GLTexture::GLTexture(const char *filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if(surface == nullptr){
        throw GLTextureException("Could not open texture file!");
    }

    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }
    createGLImage(static_cast<glm::vec4 *>(surface->pixels), surface->w, surface->h, mode);
}

void GLTexture::createGLImage(glm::vec4 *imageData, int width, int height, GLenum mode) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

GLTexture::~GLTexture() {
    glDeleteTextures(1, &textureID);
}

void GLTexture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
