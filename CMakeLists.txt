cmake_minimum_required(VERSION 3.5.0)
project(kms VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address -Wall -Wextra -pedantic")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(assimp REQUIRED)

find_package(GLEW REQUIRED)
add_executable(kms
    src/Main.cpp
    src/App.cpp
    src/Controls.cpp
    src/helpers/Callbacks.cpp
    src/helpers/ShaderLoader.cpp
    src/objects/Mesh.cpp
    src/objects/Model.cpp
    src/objects/Camera.cpp
    src/shaders/Shader.cpp
    src/shaders/Texture.cpp
    src/shaders/SkyboxTexture.cpp
    src/objects/scenes/TriangleScene.cpp
    src/objects/scenes/RectangleScene.cpp
    src/objects/scenes/TexturedScene.cpp
    src/objects/scenes/RotatingScene.cpp
    src/objects/scenes/MaterialScene.cpp
    src/objects/scenes/BezierScene.cpp
    src/objects/scenes/EmptyScene.cpp
    src/objects/scenes/SkyboxScene.cpp
    )
target_link_libraries(kms glfw GL X11 GLEW::GLEW assimp SOIL ${SDL2_LIBRARIES})