#pragma once
#include <memory>
#include <vector>
#include "Matrix.hpp"
#include "Transformation.hpp"

class TransformationComposite : public Transformation {
private:
    std::vector<std::unique_ptr<Transformation>> transformations;

public:
    TransformationComposite() = default;

    TransformationComposite(std::vector<std::unique_ptr<Transformation>> transformations) {
        this->transformations = std::move(transformations);
    }

    ~TransformationComposite() = default;

    glm::mat4 getTransformationMatrix() const override {
        glm::mat4 output = glm::mat4(1.0f);
        for (auto& transformation : transformations) {
            output = transformation->getTransformationMatrix() * output;
        }
        return output;
    }

    void addTransformationBack(std::unique_ptr<Transformation> transformation) {
        transformations.push_back(std::move(transformation));
    }

    void addTransformationFront(std::unique_ptr<Transformation> transformation) {
        transformations.insert(transformations.begin(), std::move(transformation));
    }

    void simplify() {
        auto mat = this->getTransformationMatrix();
        this->clear();
        transformations.push_back(std::make_unique<Matrix>(mat));
    }

    void clear() {
        transformations.clear();
    }

    size_t getTransformationCount() const {
        return transformations.size();
    }

    bool isEmpty() const {
        return transformations.empty();
    }
};