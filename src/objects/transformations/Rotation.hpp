#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Transformation.hpp"

class Rotation : public Transformation {
private:
    glm::vec3 rotation;

public:
    Rotation(float x, float y, float z) {
        this->rotation = glm::vec3(x, y, z);
    }

    ~Rotation() = default;

    glm::vec3 getRotation() {
        return this->rotation;
    }

    void rotate(float x, float y, float z) {
        this->rotation += glm::vec3(x, y, z);
    }

    glm::mat4 getTransformationMatrix() const override {
        auto normal_x = glm::vec3(1.0, 0.0, 0.0);
        auto normal_y = glm::vec3(0.0, 1.0, 0.0);
        auto normal_z = glm::vec3(0.0, 0.0, 1.0);

        glm::mat4 transform_matrix = glm::mat4(1.0f);

        transform_matrix = glm::rotate(transform_matrix, this->rotation.y, normal_x);
        normal_y = glm::rotate(normal_y, -rotation.y, normal_x);

        transform_matrix = glm::rotate(transform_matrix, -this->rotation.x, normal_y);
        normal_z = glm::rotate(normal_z, this->rotation.x, normal_y);

        transform_matrix = glm::rotate(transform_matrix, this->rotation.z, normal_z);
        return transform_matrix;
    }
};