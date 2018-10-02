/* Created by David Klostermann on 03.10.2018. */
#ifndef TESTBED_TEXTUREATLASRENDERER_H
#define TESTBED_TEXTUREATLASRENDERER_H

#include <map>
#include <SDL2/SDL.h>

#include "shader/glshader.h"
#include "attributebuffer/glattributebuffer.h"
#include "texture/gltexture.h"
#include "transform/transform2d.h"

class TextureAtlasRenderer {
private:
    GLShader* shader;
    SDL_Window* sdlWindow;
    GLTexture* textureAtlas;
    const int rows;
    GLAttributeBuffer<glm::vec4> buffer;

    glm::mat4 projection;

    std::map<unsigned int, std::vector<Transform2D>> renderBatch;
public:
    TextureAtlasRenderer(SDL_Window* sdlwindow, GLShader* shader, GLTexture* textureAtlas, const int rows);

    void addToRenderList(unsigned int index, Transform2D transform);

    void addToRenderList(unsigned int index, std::vector<Transform2D> transformations);

    void render();


};


#endif
