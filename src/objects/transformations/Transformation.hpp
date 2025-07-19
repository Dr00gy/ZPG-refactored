#pragma once
#include <glm/mat4x4.hpp>

class Transformation {
private:

public:
    Transformation() = default;
    ~Transformation() = default;
    virtual glm::mat4 getTransformationMatrix() const = 0;
};
