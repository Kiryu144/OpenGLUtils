/* Created by David Klostermann on 02.10.2018. */
#include "transform2d.h"

Transform2D::Transform2D(glm::vec2 position, float rotation, glm::vec2 scale) {
    this->position = position;
    this->rotation = rotation;
    this->size = scale;
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec2(0.5f);
}

Transform2D::Transform2D(glm::vec2 position, float rotation) {
    this->position = position;
    this->rotation = rotation;
    this->size = glm::vec2(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec2(0.5f);
}

Transform2D::Transform2D(glm::vec2 position) {
    this->position = position;
    this->rotation = 0;
    this->size = glm::vec2(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec2(0.5f);
}

Transform2D::Transform2D() {
    this->position = glm::vec2(0);
    this->rotation = 0;
    this->size = glm::vec2(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec2(0.5f);
}

void Transform2D::updateMatricesWhenNeeded() {
    if(updateNeeded != 0){
        glm::vec2 realRotationOrigin = rotationOrigin * size;

        matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, glm::vec3(position + realRotationOrigin, 0.0f));
        matrix = glm::rotate(matrix, rotation*float(M_PI*2), glm::vec3(0, 0, 1));
        matrix = glm::translate(matrix, glm::vec3(-realRotationOrigin, 0.0f));
        matrix = glm::scale(matrix, glm::vec3(size, 1.0f));
        updateNeeded = 0;
    }
}

const glm::mat4 &Transform2D::getMatrix() {
    updateMatricesWhenNeeded();
    return matrix;
}

void Transform2D::setPosition(glm::vec2 position) {
    this->position = position;
    updateNeeded |= POSITION;
}

const glm::vec2 &Transform2D::getPosition() {
    return position;
}

void Transform2D::translatePosition(glm::vec2 translate) {
    this->position += translate;
    updateNeeded |= POSITION;
}

void Transform2D::setRotation(float rotation) {
    this->rotation = rotation;
    updateNeeded |= ROTATION;
}

const float &Transform2D::getRotation() {
    return rotation;
}

void Transform2D::translateRotation(float translate) {
    rotation += translate;
    updateNeeded |= ROTATION;
}

void Transform2D::setSize(glm::vec2 scale) {
    this->size = scale;
    updateNeeded |= SCALE;
}

const glm::vec2 &Transform2D::getSize() {
    return size;
}

void Transform2D::translateSize(glm::vec2 scale) {
    this->size += scale;
    updateNeeded |= SCALE;
}

void Transform2D::setOrigin(glm::vec2 origin) {
    this->rotationOrigin = origin;
    updateNeeded |= PIVOT;
}

const glm::vec2 &Transform2D::getOrigin() {
    return rotationOrigin;
}
