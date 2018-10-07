/* Created by David Klostermann on 02.10.2018. */
#ifndef TESTBED_TRANSFORM2D_H
#define TESTBED_TRANSFORM2D_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <GLM/common.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtx/string_cast.hpp>
#include <GLM/gtx/euler_angles.hpp>
#include <GLM/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define POSITION    0x1
#define ROTATION    0x2
#define SCALE       0x4
#define PIVOT       0x8

//TODO: Resize around pivot

class Transform2D {
private:
    glm::vec2 position;
    float rotation;
    glm::vec2 rotationOrigin;
    glm::vec2 size;

    glm::mat4 matrix;

    int updateNeeded;

    void updateMatricesWhenNeeded();
public:
    Transform2D(glm::vec2 position, float rotation, glm::vec2 scale);
    Transform2D(glm::vec2 position, float rotation);
    Transform2D(glm::vec2 position);
    Transform2D();

    const glm::mat4& getMatrix();

    void setPosition(glm::vec2 position);
    const glm::vec2& getPosition();
    void translatePosition(glm::vec2 translate);

    void setRotation(float rotation);
    const float& getRotation();
    void translateRotation(float translate);

    void setSize(glm::vec2 scale);
    const glm::vec2& getSize();
    void translateSize(glm::vec2 scale);

    void setOrigin(glm::vec2 origin);
    const glm::vec2& getOrigin();
};


#endif
