//
// Created by Timur on 22.04.2024.
//

#ifndef OPENGL_TUTORIAL_CAMERA_H
#define OPENGL_TUTORIAL_CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
    void updateVectors();
public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::mat4 rotation;

    void rotate(float x, float y, float z);

    float fov;
    glm::vec3 position;
    Camera(glm::vec3 position, float fov);



    glm::mat4 getProjection();
    glm::mat4 getView();
};


#endif //OPENGL_TUTORIAL_CAMERA_H
