//
// Created by Timur on 23.04.2024.
//

#ifndef OPENGL_TUTORIAL_CUBE_H
#define OPENGL_TUTORIAL_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../graphics/Shader.h"

class Cube {
public:
    Cube();

    void draw(Shader *shader, glm::mat4 model);
    glm::mat4 model;
    GLuint VAO, VBO, colorbuffer;
    static float colors[108];
    static float vertices[108];
};

#endif //OPENGL_TUTORIAL_CUBE_H
