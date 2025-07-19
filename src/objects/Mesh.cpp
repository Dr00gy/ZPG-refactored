#include "Mesh.hpp"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Mesh::Mesh(MeshType type) : meshType(type), VAO(0), VBO(0), EBO(0), useIndices(false), isSetup(false) {
}

Mesh::Mesh(float* vertexData, size_t vertexCount, MeshType type) 
    : meshType(type), VAO(0), VBO(0), EBO(0), useIndices(false), isSetup(false) {
    
    vertices.reserve(vertexCount);
    
    switch (type) {
        case MeshType::BASIC:
            for (size_t i = 0; i < vertexCount * 3; i += 3) {
                vertices.emplace_back(glm::vec3(vertexData[i], vertexData[i+1], vertexData[i+2]));
            }
            break;
            
        case MeshType::NORMAL:
            for (size_t i = 0; i < vertexCount * 6; i += 6) {
                vertices.emplace_back(
                    glm::vec3(vertexData[i], vertexData[i+1], vertexData[i+2]),
                    glm::vec3(vertexData[i+3], vertexData[i+4], vertexData[i+5])
                );
            }
            break;
            
        case MeshType::UV:
            for (size_t i = 0; i < vertexCount * 8; i += 8) {
                vertices.emplace_back(
                    glm::vec3(vertexData[i], vertexData[i+1], vertexData[i+2]),
                    glm::vec3(vertexData[i+3], vertexData[i+4], vertexData[i+5]),
                    glm::vec2(vertexData[i+6], vertexData[i+7])
                );
            }
            break;
    }
}

Mesh::Mesh(float* vertexData, size_t vertexCount, unsigned int* indexData, size_t indexCount, MeshType type)
    : Mesh(vertexData, vertexCount, type) {
    
    useIndices = true;
    indices.assign(indexData, indexData + indexCount);
}

#ifdef ASSIMP_ENABLED
Mesh::Mesh(const std::string& filepath, MeshType type) : meshType(type), VAO(0), VBO(0), EBO(0), useIndices(true), isSetup(false) {
    loadFromFile(filepath);
}

void Mesh::loadFromFile(const std::string& filepath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, 
        aiProcess_Triangulate | 
        aiProcess_FlipUVs | 
        aiProcess_CalcTangentSpace |
        aiProcess_GenSmoothNormals);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    
    processNode(scene->mRootNode, scene);
}

void Mesh::processNode(aiNode* node, const aiScene* scene) {
    // Node stuff
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Mesh::processMesh(aiMesh* mesh, const aiScene* scene) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        
        // Position
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;
        
        // Normal
        if (mesh->mNormals && (meshType == MeshType::NORMAL || meshType == MeshType::UV)) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }
        
        // Texture coordinates
        if (mesh->mTextureCoords[0] && meshType == MeshType::UV) {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        
        vertices.push_back(vertex);
    }
    
    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}
#endif

void Mesh::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

void Mesh::addVertex(glm::vec3 position) {
    vertices.emplace_back(position);
}

void Mesh::addVertex(glm::vec3 position, glm::vec3 normal) {
    vertices.emplace_back(position, normal);
}

void Mesh::addVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords) {
    vertices.emplace_back(position, normal, texCoords);
}

void Mesh::addIndex(unsigned int index) {
    indices.push_back(index);
    useIndices = true;
}

void Mesh::addTriangle(unsigned int i1, unsigned int i2, unsigned int i3) {
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
    useIndices = true;
}

Mesh Mesh::createTriangle(MeshType type) {
    Mesh mesh(type);
    
    mesh.addVertex(glm::vec3(0.0f, 0.5f, 0.0f));    // Top
    mesh.addVertex(glm::vec3(-0.5f, -0.5f, 0.0f));  // Bottom-left
    mesh.addVertex(glm::vec3(0.5f, -0.5f, 0.0f));   // Bottom-right
    
    if (type == MeshType::NORMAL || type == MeshType::UV) {
        mesh.calculateNormals();
    }
    
    if (type == MeshType::UV) {
        // Basic texture coords
        mesh.vertices[0].texCoords = glm::vec2(0.5f, 1.0f);
        mesh.vertices[1].texCoords = glm::vec2(0.0f, 0.0f);
        mesh.vertices[2].texCoords = glm::vec2(1.0f, 0.0f);
    }
    
    return mesh;
}

Mesh Mesh::createSquare(MeshType type) {
    Mesh mesh(type);
    
    mesh.addVertex(glm::vec3(-0.5f, -0.5f, 0.0f));  // Bottom-left
    mesh.addVertex(glm::vec3(0.5f, -0.5f, 0.0f));   // Bottom-right
    mesh.addVertex(glm::vec3(0.5f, 0.5f, 0.0f));    // Top-right
    mesh.addVertex(glm::vec3(-0.5f, 0.5f, 0.0f));   // Top-left
    
    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(2, 3, 0);
    
    if (type == MeshType::NORMAL || type == MeshType::UV) {
        // All normals point towards +Z
        for (auto& vertex : mesh.vertices) {
            vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        }
    }
    
    if (type == MeshType::UV) {
        mesh.vertices[0].texCoords = glm::vec2(0.0f, 0.0f);
        mesh.vertices[1].texCoords = glm::vec2(1.0f, 0.0f);
        mesh.vertices[2].texCoords = glm::vec2(1.0f, 1.0f);
        mesh.vertices[3].texCoords = glm::vec2(0.0f, 1.0f);
    }
    
    return mesh;
}

Mesh Mesh::createCircle(float radius, int segments, MeshType type) {
    Mesh mesh(type);
    
    // Center vertex
    mesh.addVertex(glm::vec3(0.0f, 0.0f, 0.0f));
    
    // Edge vertices
    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * M_PI / segments;
        mesh.addVertex(glm::vec3(radius * cos(angle), radius * sin(angle), 0.0f));
    }
    
    if (type == MeshType::NORMAL || type == MeshType::UV) {
        for (auto& vertex : mesh.vertices) {
            vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        }
    }
    
    if (type == MeshType::UV) {
        mesh.vertices[0].texCoords = glm::vec2(0.5f, 0.5f); // Center
        for (int i = 1; i < mesh.vertices.size(); ++i) {
            float angle = (i - 1) * 2.0f * M_PI / segments;
            mesh.vertices[i].texCoords = glm::vec2(
                0.5f + 0.5f * cos(angle),
                0.5f + 0.5f * sin(angle)
            );
        }
    }
    
    return mesh;
}

Mesh Mesh::createCube(MeshType type) {
    Mesh mesh(type);
    std::vector<glm::vec3> positions = {
        // Front face
        {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f},
        // Back face
        {-1.0f, -1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f},
        // Top face
        {-1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, { 1.0f,  1.0f, -1.0f},
        // Bottom face
        {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f,  1.0f}, {-1.0f, -1.0f,  1.0f},
        // Right face
        { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f},
        // Left face
        {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f, -1.0f}
    };
    
    std::vector<glm::vec3> normals = {
        // Front, Back, Top, Bottom, Right, Left
        { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  1.0f,  0.0f},
        { 0.0f, -1.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}
    };
    
    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
    };
    
    for (int face = 0; face < 6; ++face) {
        for (int i = 0; i < 4; ++i) {
            Vertex vertex;
            vertex.position = positions[face * 4 + i];
            if (type == MeshType::NORMAL || type == MeshType::UV) {
                vertex.normal = normals[face];
            }
            if (type == MeshType::UV) {
                vertex.texCoords = texCoords[i];
            }
            mesh.addVertex(vertex);
        }
        
        // 2 triangles per face
        int baseIndex = face * 4;
        mesh.addTriangle(baseIndex, baseIndex + 1, baseIndex + 2);
        mesh.addTriangle(baseIndex + 2, baseIndex + 3, baseIndex);
    }
    
    return mesh;
}

Mesh Mesh::createPlane(MeshType type) {
    Mesh mesh(type);
    
    mesh.addVertex(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
    mesh.addVertex(glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f));
    mesh.addVertex(glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f));
    mesh.addVertex(glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f));
    
    mesh.addTriangle(0, 1, 2);
    mesh.addTriangle(2, 3, 0);
    
    return mesh;
}

void Mesh::setupMesh() {
    if (isSetup) return;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    if (useIndices && !indices.empty()) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
    
    setupVertexAttributes();
    glBindVertexArray(0);
    
    isSetup = true;
}

void Mesh::setupVertexAttributes() {
    switch (meshType) {
        case MeshType::BASIC:
            // Position attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
            break;
            
        case MeshType::NORMAL:
            // Position attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
            // Normal attrib
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(1);
            break;
            
        case MeshType::UV:
            // Position attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
            // Normal attrib
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glEnableVertexAttribArray(1);
            // Texture coordinate attrib
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
            glEnableVertexAttribArray(2);
            break;
    }
}

void Mesh::calculateNormals() {
    for (auto& vertex : vertices) {
        vertex.normal = glm::vec3(0.0f);
    }
    
    // Calculates face normals and accumulate
    if (useIndices) {
        for (size_t i = 0; i < indices.size(); i += 3) {
            glm::vec3& v0 = vertices[indices[i]].position;
            glm::vec3& v1 = vertices[indices[i + 1]].position;
            glm::vec3& v2 = vertices[indices[i + 2]].position;
            
            glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
            
            vertices[indices[i]].normal += normal;
            vertices[indices[i + 1]].normal += normal;
            vertices[indices[i + 2]].normal += normal;
        }
    } else {
        for (size_t i = 0; i < vertices.size(); i += 3) {
            glm::vec3& v0 = vertices[i].position;
            glm::vec3& v1 = vertices[i + 1].position;
            glm::vec3& v2 = vertices[i + 2].position;
            
            glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
            
            vertices[i].normal += normal;
            vertices[i + 1].normal += normal;
            vertices[i + 2].normal += normal;
        }
    }
    
    // Normalizes accumulated normals
    for (auto& vertex : vertices) {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

size_t Mesh::getVertexCount() const {
    return vertices.size();
}

size_t Mesh::getIndexCount() const {
    return indices.size();
}

void Mesh::cleanup() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    isSetup = false;
}

Mesh::~Mesh() {
    cleanup();
}