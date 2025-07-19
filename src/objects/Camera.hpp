#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    float yaw;
    float pitch;
    
    float movementSpeed;
    float mouseSensitivity;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    
    //Scalar and vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), 
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float yaw = YAW, 
           float pitch = PITCH);
    
    Camera(float posX, float posY, float posZ, 
           float upX, float upY, float upZ, 
           float yaw, float pitch);
    
    // We get view matrix calculated using Euler angles and the LookAt Matrix
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
    void updateAspectRatio(float width, float height);
    
    float getFOV() const { return fov; }
    float getAspectRatio() const { return aspectRatio; }
    float getNearPlane() const { return nearPlane; }
    float getFarPlane() const { return farPlane; }
    void setFOV(float newFov) { fov = newFov; }
    void setAspectRatio(float newAspectRatio) { aspectRatio = newAspectRatio; }
    void setPlanes(float near, float far) { nearPlane = near; farPlane = far; }
    
private:
    // FRONT vector from the camera (updated) Euler angles
    void updateCameraVectors();
};