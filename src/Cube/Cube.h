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
    glm::vec3 up_vec ;
    glm::vec3 front_vec;
    glm::vec3 right_vec;
    int x, y ,z;
    int id;
    Cube();
    glm::vec3 white_n;
    glm::vec3 blue_n;
    glm::vec3 red_n;
    glm::vec3 yellow_n();
    glm::vec3 orange_n();
    glm::vec3 green_n();
    void draw(Shader *shader, glm::mat4 model);
    glm::mat4 model;
    GLuint VAO, VBO, colorbuffer;
    static float colors[108];
    static float vertices[108];
    char get_color_by_n(glm::vec3 n);
};

#endif //OPENGL_TUTORIAL_CUBE_H
