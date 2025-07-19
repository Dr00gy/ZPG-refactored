#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "Transformation.hpp"

class Translation : public Transformation { // Inheritance
private:
    glm::vec3 translation;

public:
    Translation(float x, float y, float z) {
        this->translation = glm::vec3(x, y, z);
    }

    ~Translation() = default;

    glm::mat4 getTransformationMatrix() {
        return glm::translate(glm::mat4(1.0f), this->translation);
    }
};

#endif // TRANSLATION_H