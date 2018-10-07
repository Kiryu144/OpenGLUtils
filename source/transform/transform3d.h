/* Created by David Klostermann on 07.10.2018. */
#ifndef TESTBED_TRANSFORM3D_H
#define TESTBED_TRANSFORM3D_H

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

class Transform3D {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 rotationOrigin;
    glm::vec3 size;

    glm::mat4 matrix;

    int updateNeeded;

    void updateMatricesWhenNeeded();
public:
    Transform3D(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Transform3D(glm::vec3 position, glm::vec3 rotation);
    Transform3D(glm::vec3 position);
    Transform3D();

    const glm::mat4& getMatrix();

    void setPosition(glm::vec3 position);
    const glm::vec3& getPosition();
    void translatePosition(glm::vec3 translate);

    void setRotation(glm::vec3 rotation);
    const glm::vec3& getRotation();
    void translateRotation(glm::vec3 translate);

    void setSize(glm::vec3 scale);
    const glm::vec3& getSize();
    void translateSize(glm::vec3 scale);

    void setOrigin(glm::vec3 origin);
    const glm::vec3& getOrigin();
};


#endif
