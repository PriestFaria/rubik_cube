
#include <GL/glew.h>
#include "../graphics/Shader.h"
class Cube {
public:
    Cube(float* vertices, float* colors, size_t vertices_size, size_t colors_size) : vertices(vertices), colors(colors) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &colorbuffer);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw(Shader* shader, glm::mat4 model) {
        shader->use();
        shader->uniformMatrix("model", model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

private:
    float* vertices;
    float* colors;
    GLuint VAO, VBO, colorbuffer;
};
