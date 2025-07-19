#pragma once
#include "Mesh.hpp"
#include "transformations/TransformationComposite.hpp"
#include "transformations/Translation.hpp"
#include "transformations/Rotation.hpp"
#include "transformations/Scale.hpp"
#include "transformations/Identity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class Model {
public:
    std::vector<std::shared_ptr<Mesh>> meshes;
    
    // Keeping basic transforms for now
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    TransformationComposite transformations;
    
    Model();
    Model(std::shared_ptr<Mesh> mesh);
    Model(const std::string& filepath, MeshType type = MeshType::UV);
    
    void setPosition(float x, float y, float z);
    void setPosition(const glm::vec3& pos);
    void translate(float x, float y, float z);
    void translate(const glm::vec3& translation);
    
    void setRotation(float x, float y, float z);
    void setRotation(const glm::vec3& rot);
    void rotate(float x, float y, float z);
    void rotate(const glm::vec3& rotation);
    
    void setScale(float x, float y, float z);
    void setScale(const glm::vec3& scl);
    void setScale(float uniformScale);
    
    void addTransformation(std::unique_ptr<Transformation> transformation);
    void addTransformationFront(std::unique_ptr<Transformation> transformation);
    void clearTransformations();
    void simplifyTransformations();
    
    // Matrix ops
    glm::mat4 getModelMatrix() const;
    glm::mat4 getBasicModelMatrix() const; // Uses only position, rotation, scale!
    glm::mat4 getCompositeModelMatrix() const; // Uses transformation composite!
    
    // Mesh ops
    void addMesh(std::shared_ptr<Mesh> mesh);
    void setupAllMeshes();
    
    void draw();
    void draw(GLenum mode); // Custom draw mode (GL_TRIANGLES, GL_LINES, etc.)
    
    // Utility
    size_t getMeshCount() const;
    std::shared_ptr<Mesh> getMesh(size_t index) const;
    
    void cleanup();
    
    ~Model();
    
    // Factory methods common shapes
    static std::shared_ptr<Model> createTriangle(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createSquare(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createCircle(float radius = 1.0f, int segments = 100, MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createCube(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createPlane(MeshType type = MeshType::UV);

private:
    void loadModel(const std::string& filepath, MeshType type);
    void updateTransformationComposite(); // Sync basic transforms with composite
};