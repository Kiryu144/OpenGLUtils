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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, imageData);
}

GLTexture::~GLTexture() {
    glDeleteTextures(1, &textureID);
}

void GLTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}
