/* Created by David Klostermann on 07.10.2018. */
#include "transform3d.h"

Transform3D::Transform3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->size = scale;
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec3(0.5f);
}

Transform3D::Transform3D(glm::vec3 position, glm::vec3 rotation) {
    this->position = position;
    this->rotation = rotation;
    this->size = glm::vec3(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec3(0.5f);
}

Transform3D::Transform3D(glm::vec3 position) {
    this->position = position;
    this->rotation = glm::vec3(0);
    this->size = glm::vec3(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec3(0.5f);
}

Transform3D::Transform3D() {
    this->position = glm::vec3(0);
    this->rotation = glm::vec3(0);
    this->size = glm::vec3(1);
    updateNeeded |= (POSITION | ROTATION | SCALE);
    matrix = glm::mat4(1);
    rotationOrigin = glm::vec3(0.5f);
}

void Transform3D::updateMatricesWhenNeeded() {
    if(updateNeeded != 0){
        glm::vec3 realRotationOrigin = rotationOrigin * size;

        matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, position + realRotationOrigin);
        matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
        matrix = glm::translate(matrix, -realRotationOrigin);
        matrix = glm::scale(matrix, size);
        updateNeeded = 0;
    }
}

const glm::mat4 &Transform3D::getMatrix() {
    updateMatricesWhenNeeded();
    return matrix;
}

void Transform3D::setPosition(glm::vec3 position) {
    this->position = position;
    updateNeeded |= POSITION;
}

const glm::vec3 &Transform3D::getPosition() {
    return position;
}

void Transform3D::translatePosition(glm::vec3 translate) {
    this->position += translate;
    updateNeeded |= POSITION;
}

void Transform3D::setRotation(glm::vec3 rotation) {
    this->rotation = rotation;
    updateNeeded |= ROTATION;
}

const glm::vec3 &Transform3D::getRotation() {
    return rotation;
}

void Transform3D::translateRotation(glm::vec3 translate) {
    rotation += translate;
    updateNeeded |= ROTATION;
}

void Transform3D::setSize(glm::vec3 scale) {
    this->size = scale;
    updateNeeded |= SCALE;
}

const glm::vec3 &Transform3D::getSize() {
    return size;
}

void Transform3D::translateSize(glm::vec3 scale) {
    this->size += scale;
    updateNeeded |= SCALE;
}

void Transform3D::setOrigin(glm::vec3 origin) {
    this->rotationOrigin = origin;
    updateNeeded |= PIVOT;
}

const glm::vec3 &Transform3D::getOrigin() {
    return rotationOrigin;
}