
#include <GL/glew.h>
#include "../graphics/Shader.h"

class Cube {
public:
    Cube(float *vertices, size_t size) : vertices(vertices) {
        float colors[108] = {
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

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &colorbuffer);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,size, vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw(Shader *shader, glm::mat4 model) {
        shader->use();
        shader->uniformMatrix("model", model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

private:

    float *vertices;
    GLuint VAO, VBO, colorbuffer;
    float *colors;
};

