/* Created by David Klostermann on 03.10.2018. */
#include "textureatlasrenderer.h"

TextureAtlasRenderer::TextureAtlasRenderer(SDL_Window* sdlwindow, GLShader* shader, GLTexture* textureAtlas, const int rows) : rows(rows) {
    this->textureAtlas = textureAtlas;
    this->shader = shader;
    this->sdlWindow = sdlwindow;

    float i = 1.0f/float(rows);
    std::vector<glm::vec4> vertexData;
    vertexData.push_back(glm::vec4(0, 1, 0, i));
    vertexData.push_back(glm::vec4(1, 0, i, 0));
    vertexData.push_back(glm::vec4(0, 0, 0, 0));
    vertexData.push_back(glm::vec4(0, 1, 0, i));
    vertexData.push_back(glm::vec4(1, 1, i, i));
    vertexData.push_back(glm::vec4(1, 0, i, 0));
    buffer.upload(vertexData);

    //TODO: Implement auto-updating of width/height and mat4
    int width, height;
    SDL_GetWindowSize(sdlWindow, &width, &height);
    projection = glm::ortho(0.0f, float(width), float(height), 0.0f);
}

void TextureAtlasRenderer::addToRenderList(unsigned int index, Transform2D transform) {
    std::map<unsigned int, std::vector<Transform2D>>::iterator it;
    for(it = renderBatch.find(index); it == renderBatch.end();){
        renderBatch.insert(std::pair<unsigned int, std::vector<Transform2D>>(index, std::vector<Transform2D>()));
        it = renderBatch.find(index);
    }
    it->second.push_back(transform);
}

void TextureAtlasRenderer::addToRenderList(unsigned int index, std::vector<Transform2D> transformations) {
    std::map<unsigned int, std::vector<Transform2D>>::iterator it;
    for(it = renderBatch.find(index); it == renderBatch.end();){
        renderBatch.insert(std::pair<unsigned int, std::vector<Transform2D>>(index, std::vector<Transform2D>()));
        it = renderBatch.find(index);
    }
    for(Transform2D transform : transformations){
        it->second.push_back(transform);
    }
}

void TextureAtlasRenderer::render() {
    if(renderBatch.size() > 0){
        shader->bind();
        this->shader->setUniform("projection", projection);
        textureAtlas->bind();
        buffer.bind(0);
    }else{
        return;
    }

    for(auto it = renderBatch.begin(); it != renderBatch.end(); it++){
        unsigned int index = it->first;
        shader->setUniform("atlasdata", glm::vec2(index, rows));
        for(Transform2D& transform : it->second){
            shader->setUniform("model", transform.getMatrix());
            glGetError();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    renderBatch.clear();
}
