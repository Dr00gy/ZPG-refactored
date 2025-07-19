#pragma once
#include <memory>
#include <vector>
#include "Matrix.hpp"
#include "Transformation.hpp"

class TransformationComposite : public Transformation { // Inheritance, polymorphism
private:
    std::vector<Transformation*> transformations;

public:
    TransformationComposite() = default;

    TransformationComposite(std::vector<Transformation*> transformations) {
        transformations = transformations;
    }

    ~TransformationComposite() {
        for (auto transformation : transformations) {
            delete transformation;
        }
    }

    glm::mat4 getTransformationMatrix() {
        glm::mat4 output = glm::mat4(1.0f);
        for (auto& transformation : transformations) {
            output = transformation->getTransformationMatrix() * output;
        }
        return output;
    }

    void addTransformationBack(Transformation* transformation) {
        transformations.push_back(std::move(transformation));
    }

    void addTransformationFront(Transformation* transformation) {
        transformations.insert(transformations.begin(), std::move(transformation));
    }

    void simplify() {
        auto mat = this->getTransformationMatrix();
        this->clear();
        transformations.push_back(new Matrix(mat));
    }

    void clear(){
        for (auto transformation : transformations) {
            delete transformation;
        }
        transformations.clear();
    }
};