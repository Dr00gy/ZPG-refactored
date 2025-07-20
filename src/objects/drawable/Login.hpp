#pragma once
#include "../Model.hpp"
#include "../../shaders/Material.hpp"
#include "../../shaders/Shader.hpp"
#include <memory>

class Login : public Model {
public:
    static constexpr const char* LOGIN_MODEL_PATH = "../../../models/dalin.obj";
    
    Login(MeshType type = MeshType::UV);
    Login(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);
    
    static std::shared_ptr<Login> create(MeshType type = MeshType::UV);
    static std::shared_ptr<Login> create(MeshType type, std::shared_ptr<Material> mat, std::shared_ptr<Shader> shd);

private:
    void setupDefaultShaderAndMaterial();
};