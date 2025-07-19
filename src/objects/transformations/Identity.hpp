#pragma once
#include "Transformation.hpp"

class Identity : public Transformation {
public:
    Identity() = default;
    ~Identity() = default;

    glm::mat4 getTransformationMatrix() const override {
        return glm::mat4(1.0f);
    }
};