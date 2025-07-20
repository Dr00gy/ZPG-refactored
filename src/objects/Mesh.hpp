#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#ifdef ASSIMP_ENABLED
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

enum class MeshType {
    BASIC,    // positions only
    NORMAL,   // positions + normals
    UV        // positions + normals + texture coordinates
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    
    Vertex() : position(0.0f), normal(0.0f), texCoords(0.0f) {}
    Vertex(glm::vec3 pos) : position(pos), normal(0.0f), texCoords(0.0f) {}
    Vertex(glm::vec3 pos, glm::vec3 norm) : position(pos), normal(norm), texCoords(0.0f) {}
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex) : position(pos), normal(norm), texCoords(tex) {}
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    MeshType meshType;
    GLuint VAO, VBO, EBO;
    bool useIndices;
    
    Mesh(MeshType type = MeshType::BASIC);
    
    // Load from raw vertex data or a file here
    Mesh(float* vertexData, size_t vertexCount, MeshType type);
    Mesh(float* vertexData, size_t vertexCount, unsigned int* indexData, size_t indexCount, MeshType type);
    
    #ifdef ASSIMP_ENABLED
    Mesh(const std::string& filepath, MeshType type = MeshType::UV);
    #endif
    
    void addVertex(const Vertex& vertex);
    void addVertex(glm::vec3 position);
    void addVertex(glm::vec3 position, glm::vec3 normal);
    void addVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords);
    
    void addIndex(unsigned int index);
    void addTriangle(unsigned int i1, unsigned int i2, unsigned int i3);
    
    // Common shapes on the go
    static Mesh createTriangle(MeshType type = MeshType::BASIC);
    static Mesh createSquare(MeshType type = MeshType::BASIC);
    static Mesh createCircle(float radius = 1.0f, int segments = 100, MeshType type = MeshType::BASIC);
    
    // OpenGL buffers
    void setupMesh();
    
    // Utility
    void calculateNormals();
    void generateTextureCoords();
    size_t getVertexCount() const;
    size_t getIndexCount() const;
    
    void cleanup();
    
    ~Mesh();

private:
    bool isSetup;
    
    void setupVertexAttributes();
    
    #ifdef ASSIMP_ENABLED
    void loadFromFile(const std::string& filepath);
    void processNode(aiNode* node, const aiScene* scene);
    void processMesh(aiMesh* mesh, const aiScene* scene);
    #endif
};