#pragma once
#include "../Model.hpp"

class Login : public Model {
public:
    static constexpr const char* LOGIN_MODEL_PATH = "../../../models/dalin.obj";
    
    Login(MeshType type = MeshType::UV);
    
    // Factory method for convenience
    static std::shared_ptr<Login> create(MeshType type = MeshType::UV);
};