/* Created by David Klostermann on 02.10.2018. */
#ifndef TESTBED_TEXTURERENDERER_H
#define TESTBED_TEXTURERENDERER_H

#include <map>
#include <SDL2/SDL.h>

#include "shader/glshader.h"
#include "attributebuffer/glattributebuffer.h"
#include "texture/gltexture.h"
#include "transform/transform2d.h"

class TextureRenderer {
private:
    GLShader* shader;
    SDL_Window* sdlWindow;
    GLAttributeBuffer<glm::vec4> buffer;

    glm::mat4 projection;

    std::map<GLTexture*, std::vector<Transform2D>> renderBatch;
public:
    TextureRenderer(SDL_Window* sdlWindow, GLShader* shader);

    void addToRenderList(GLTexture* texture, Transform2D transform);

    void addToRenderList(GLTexture* texture, std::vector<Transform2D>& transformations);

    void render();
};


#endif
