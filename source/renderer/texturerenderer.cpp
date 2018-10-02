/* Created by David Klostermann on 02.10.2018. */
#include "texturerenderer.h"

TextureRenderer::TextureRenderer(SDL_Window* sdlWindow, GLShader *shader) {
    this->sdlWindow = sdlWindow;
    this->shader = shader;

    std::vector<glm::vec4> vertexData;
    vertexData.push_back(glm::vec4(0, 1, 0, 1));
    vertexData.push_back(glm::vec4(1, 0, 1, 0));
    vertexData.push_back(glm::vec4(0, 0, 0, 0));
    vertexData.push_back(glm::vec4(0, 1, 0, 1));
    vertexData.push_back(glm::vec4(1, 1, 1, 1));
    vertexData.push_back(glm::vec4(1, 0, 1, 0));
    buffer.upload(vertexData);

    //TODO: Implement auto-updating of width/height and mat4
    int width, height;
    SDL_GetWindowSize(sdlWindow, &width, &height);
    projection = glm::ortho(0.0f, float(width), float(height), 0.0f);
}

void TextureRenderer::addToRenderList(GLTexture* texture, Transform2D transform){
    std::map<GLTexture*, std::vector<Transform2D>>::iterator it;
    for(it = renderBatch.find(texture); it == renderBatch.end();){
        renderBatch.insert(std::pair<GLTexture*, std::vector<Transform2D>>(texture, std::vector<Transform2D>()));
        it = renderBatch.find(texture);
    }
    it->second.push_back(transform);
}

void TextureRenderer::addToRenderList(GLTexture* texture, std::vector<Transform2D>& transformations){
    std::map<GLTexture*, std::vector<Transform2D>>::iterator it;
    for(it = renderBatch.find(texture); it == renderBatch.end();){
        renderBatch.insert(std::pair<GLTexture*, std::vector<Transform2D>>(texture, std::vector<Transform2D>()));
        it = renderBatch.find(texture);
    }
    for(Transform2D& transform : transformations){
        it->second.push_back(transform);
    }
}

void TextureRenderer::render() {
    if(renderBatch.size() > 0){
        shader->bind();
        this->shader->setUniform("projection", projection);
        buffer.bind(0);
    }else{
        return;
    }

    for(auto it = renderBatch.begin(); it != renderBatch.end(); it++){
        it->first->bind(); //Bind texture
        for(Transform2D& transform : it->second){
            shader->setUniform("model", transform.getMatrix());
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    renderBatch.clear();
}
