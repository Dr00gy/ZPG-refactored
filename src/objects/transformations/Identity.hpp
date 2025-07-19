#pragma once
#include "Transformation.hpp"

class Identity : public Transformation { // Inheritance
public:
    Identity() = default;
    ~Identity() = default;

    glm::mat4 getTransformationMatrix() {
        return glm::mat4(1.0f);
    }
};

