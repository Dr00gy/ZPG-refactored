#pragma once
#include "Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class Model {
public:
    std::vector<std::shared_ptr<Mesh>> meshes;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    Model();
    Model(std::shared_ptr<Mesh> mesh);
    Model(const std::string& filepath, MeshType type = MeshType::UV);
    
    // Transform operations
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
    
    // Matrix ops
    glm::mat4 getModelMatrix() const;
    
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
    
    // Factory methods common shap
    static std::shared_ptr<Model> createTriangle(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createSquare(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createCircle(float radius = 1.0f, int segments = 100, MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createCube(MeshType type = MeshType::BASIC);
    static std::shared_ptr<Model> createPlane(MeshType type = MeshType::UV);

private:
    void loadModel(const std::string& filepath, MeshType type);
};