#include "Login.hpp"
#include <iostream>

Login::Login(MeshType type) : Model() {
    #ifdef ASSIMP_ENABLED
    loadModel(LOGIN_MODEL_PATH, type);
    #else
    std::cerr << "ERROR: Assimp not enabled. Cannot load login model from: " << LOGIN_MODEL_PATH << std::endl;
    #endif
}

std::shared_ptr<Login> Login::create(MeshType type) {
    return std::make_shared<Login>(type);
}