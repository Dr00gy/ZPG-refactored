#include "House.hpp"
#include <iostream>

House::House(MeshType type) : Model() {
    #ifdef ASSIMP_ENABLED
    loadModel(HOUSE_MODEL_PATH, type);
    #else
    std::cerr << "ERROR: Assimp not enabled. Cannot load house model from: " << HOUSE_MODEL_PATH << std::endl;
    #endif
}

std::shared_ptr<House> House::create(MeshType type) {
    return std::make_shared<House>(type);
}