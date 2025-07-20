#include "Creature.hpp"
#include <iostream>

Creature::Creature(MeshType type) : Model() {
    #ifdef ASSIMP_ENABLED
    loadModel(CREATURE_MODEL_PATH, type);
    #else
    std::cerr << "ERROR: Assimp not enabled. Cannot load creature model from: " << CREATURE_MODEL_PATH << std::endl;
    #endif
}

std::shared_ptr<Creature> Creature::create(MeshType type) {
    return std::make_shared<Creature>(type);
}