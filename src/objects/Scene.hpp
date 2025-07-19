#define GLM_ENABLE_EXPERIMENTAL
#pragma once

class Scene {
public:
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(float deltaTime) {}
    virtual void render() = 0;
    virtual void cleanup() = 0;
};