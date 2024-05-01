
#include <GL/glew.h>
#include "../graphics/Shader.h"
#include "Cube.h"

Cube::Cube() {
    white_n = glm::vec3(0.0f, 0.0f, -1.0f);
    blue_n = glm::vec3(1.0f, 0.0f, 0.0f);
    red_n = glm::vec3(0.0f, 1.0f, 0.0f);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &colorbuffer);
    model = glm::mat4(1.0f);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cube::draw(Shader *shader, glm::mat4 model) {
    shader->use();
    shader->uniformMatrix("model", model);
    glBindVertexArray(Cube::VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


float Cube::colors[108] = {
        //left down
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        //back up
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        //bottom_up
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,



        //back_down
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        //left up
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        // bottom down
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,

        //front_down
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        //right_up
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        //right down
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        //up up
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        //up down
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        //front up
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
};


float Cube::vertices[108] = {-1.0f, -1.0f, -1.0f,
                             -1.0f, -1.0f, 1.0f,
                             -1.0f, 1.0f, 1.0f,
                             1.0f, 1.0f, -1.0f,
                             -1.0f, -1.0f, -1.0f,
                             -1.0f, 1.0f, -1.0f,
                             1.0f, -1.0f, 1.0f,
                             -1.0f, -1.0f, -1.0f,
                             1.0f, -1.0f, -1.0f,
                             1.0f, 1.0f, -1.0f,
                             1.0f, -1.0f, -1.0f,
                             -1.0f, -1.0f, -1.0f,
                             -1.0f, -1.0f, -1.0f,
                             -1.0f, 1.0f, 1.0f,
                             -1.0f, 1.0f, -1.0f,
                             1.0f, -1.0f, 1.0f,
                             -1.0f, -1.0f, 1.0f,
                             -1.0f, -1.0f, -1.0f,
                             -1.0f, 1.0f, 1.0f,
                             -1.0f, -1.0f, 1.0f,
                             1.0f, -1.0f, 1.0f,
                             1.0f, 1.0f, 1.0f,
                             1.0f, -1.0f, -1.0f,
                             1.0f, 1.0f, -1.0f,
                             1.0f, -1.0f, -1.0f,
                             1.0f, 1.0f, 1.0f,
                             1.0f, -1.0f, 1.0f,
                             1.0f, 1.0f, 1.0f,
                             1.0f, 1.0f, -1.0f,
                             -1.0f, 1.0f, -1.0f,
                             1.0f, 1.0f, 1.0f,
                             -1.0f, 1.0f, -1.0f,
                             -1.0f, 1.0f, 1.0f,
                             1.0f, 1.0f, 1.0f,
                             -1.0f, 1.0f, 1.0f,
                             1.0f, -1.0f, 1.0f
};


glm::vec3 Cube::orange_n() {
    return -red_n;
}

glm::vec3 Cube::green_n() {
    return -blue_n;
}

glm::vec3 Cube::yellow_n() {
    return -white_n;
}


