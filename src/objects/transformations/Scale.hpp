#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "Transformation.hpp"

class Scale : public Transformation { // Inheritance
private:
    glm::vec3 scale;

public:
    Scale(float x, float y, float z) {
        this->scale = glm::vec3(x, y, z);
    }
    
    ~Scale() = default;

    glm::mat4 getTransformationMatrix() {
        return glm::scale(glm::mat4(1.0f), this->scale);
    }
};