#define GLM_ENABLE_EXPERIMENTAL
#include "Model.hpp"
#include <iostream>

Model::Model() : position(0.0f), rotation(0.0f), scale(1.0f) {
    updateTransformationComposite();
}

Model::Model(std::shared_ptr<Mesh> mesh) : position(0.0f), rotation(0.0f), scale(1.0f) {
    addMesh(mesh);
    updateTransformationComposite();
}

Model::Model(const std::string& filepath, MeshType type) : position(0.0f), rotation(0.0f), scale(1.0f) {
    loadModel(filepath, type);
    updateTransformationComposite();
}

void Model::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    updateTransformationComposite();
}

void Model::setPosition(const glm::vec3& pos) {
    position = pos;
    updateTransformationComposite();
}

void Model::translate(float x, float y, float z) {
    position += glm::vec3(x, y, z);
    updateTransformationComposite();
}

void Model::translate(const glm::vec3& translation) {
    position += translation;
    updateTransformationComposite();
}

void Model::setRotation(float x, float y, float z) {
    rotation = glm::vec3(x, y, z);
    updateTransformationComposite();
}

void Model::setRotation(const glm::vec3& rot) {
    rotation = rot;
    updateTransformationComposite();
}

void Model::rotate(float x, float y, float z) {
    rotation += glm::vec3(x, y, z);
    updateTransformationComposite();
}

void Model::rotate(const glm::vec3& rot) {
    rotation += rot;
    updateTransformationComposite();
}

void Model::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
    updateTransformationComposite();
}

void Model::setScale(const glm::vec3& scl) {
    scale = scl;
    updateTransformationComposite();
}

void Model::setScale(float uniformScale) {
    scale = glm::vec3(uniformScale);
    updateTransformationComposite();
}

void Model::addTransformation(std::unique_ptr<Transformation> transformation) {
    transformations.addTransformationBack(std::move(transformation));
}

void Model::addTransformationFront(std::unique_ptr<Transformation> transformation) {
    transformations.addTransformationFront(std::move(transformation));
}

void Model::clearTransformations() {
    transformations.clear();
    updateTransformationComposite();
}

void Model::simplifyTransformations() {
    transformations.simplify();
}

glm::mat4 Model::getModelMatrix() const {
    return getCompositeModelMatrix();
}

glm::mat4 Model::getBasicModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    
    return model;
}

glm::mat4 Model::getCompositeModelMatrix() const {
    return transformations.getTransformationMatrix();
}

void Model::updateTransformationComposite() {
    // Clear existing basic transforms to rebuild them
    transformations.clear();
    
    // In order: Scale -> Rotate -> Translate
    
    if (scale != glm::vec3(1.0f)) {
        transformations.addTransformationBack(std::make_unique<Scale>(scale.x, scale.y, scale.z));
    }
    
    if (rotation != glm::vec3(0.0f)) {
        transformations.addTransformationBack(std::make_unique<Rotation>(rotation.x, rotation.y, rotation.z));
    }
    
    if (position != glm::vec3(0.0f)) {
        transformations.addTransformationBack(std::make_unique<Translation>(position.x, position.y, position.z));
    }
}

void Model::addMesh(std::shared_ptr<Mesh> mesh) {
    meshes.push_back(mesh);
}

void Model::setupAllMeshes() {
    for (auto& mesh : meshes) {
        mesh->setupMesh();
    }
}

void Model::draw() {
    draw(GL_TRIANGLES);
}

void Model::draw(GLenum mode) {
    for (auto& mesh : meshes) {
        if (!mesh) continue;
        
        if (mesh->VAO == 0) {
            mesh->setupMesh();
        }
        
        glBindVertexArray(mesh->VAO);
        
        if (mesh->useIndices && !mesh->indices.empty()) {
            glDrawElements(mode, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(mode, 0, mesh->vertices.size());
        }
        
        glBindVertexArray(0);
    }
}

size_t Model::getMeshCount() const {
    return meshes.size();
}

std::shared_ptr<Mesh> Model::getMesh(size_t index) const {
    if (index < meshes.size()) {
        return meshes[index];
    }
    return nullptr;
}

void Model::cleanup() {
    for (auto& mesh : meshes) {
        if (mesh) {
            mesh->cleanup();
        }
    }
    meshes.clear();
    transformations.clear();
}

Model::~Model() {
    cleanup();
}

void Model::loadModel(const std::string& filepath, MeshType type) {
    #ifdef ASSIMP_ENABLED
    auto mesh = std::make_shared<Mesh>(filepath, type);
    addMesh(mesh);
    #else
    std::cerr << "ERROR: Assimp not enabled. Cannot load model from file: " << filepath << std::endl;
    #endif
}

// Factory methods
std::shared_ptr<Model> Model::createTriangle(MeshType type) {
    auto mesh = std::make_shared<Mesh>(Mesh::createTriangle(type));
    return std::make_shared<Model>(mesh);
}

std::shared_ptr<Model> Model::createSquare(MeshType type) {
    auto mesh = std::make_shared<Mesh>(Mesh::createSquare(type));
    return std::make_shared<Model>(mesh);
}

std::shared_ptr<Model> Model::createCircle(float radius, int segments, MeshType type) {
    auto mesh = std::make_shared<Mesh>(Mesh::createCircle(radius, segments, type));
    return std::make_shared<Model>(mesh);
}

std::shared_ptr<Model> Model::createCube(MeshType type) {
    auto mesh = std::make_shared<Mesh>(Mesh::createCube(type));
    return std::make_shared<Model>(mesh);
}

std::shared_ptr<Model> Model::createPlane(MeshType type) {
    auto mesh = std::make_shared<Mesh>(Mesh::createPlane(type));
    return std::make_shared<Model>(mesh);
}