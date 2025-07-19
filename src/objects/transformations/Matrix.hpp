#pragma once
#include "Transformation.hpp"

class Matrix : public Transformation { // Inheritance
private:
    glm::mat4 matrix;

public:
    Matrix() { matrix = glm::mat4(1.0f); }
    Matrix(glm::mat4 mat) { matrix = mat; }
    ~Matrix();

    glm::mat4 getTransformationMatrix() {
        return this->matrix;
    }
};