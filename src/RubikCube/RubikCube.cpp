//
// Created by Timur on 23.04.2024.
//

#include "RubikCube.h"

RubikCube::RubikCube(Shader *shader) : shader(shader) {
    cubes = std::vector<std::vector<std::vector<Cube> > >(3, std::vector<std::vector<Cube> >(3, std::vector<Cube>(3,
                                                                                                                  Cube())));
    make_grid();
}

void RubikCube::draw() {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                draw_cube(x, y, z);
            }
        }
    }
}

void RubikCube::make_grid() {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                cubes[x][y][z].model = glm::translate(cubes[x][y][z].model,
                                                      glm::vec3((float) (1.0f * x), (float) (1.0f * y),
                                                                (float) (1.0f * z)));
            }
        }
    }
}

void RubikCube::draw_cube(int x, int y, int z) {
    cubes[x][y][z].draw(shader, cubes[x][y][z].model);
}

void RubikCube::rotate_horizontal(int layer) {
    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec3 center = glm::vec3(2.0f, 3.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f),
                                             glm::vec3(0.0f, -1.0f, 0.0f));
            glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                   -center); // Перемещаем в противоположную сторону от центра
            glm::mat4 invTranslation = glm::translate(glm::mat4(1.0),
                                                      center); // Возвращаем кубики обратно после вращения
            cubes[x][layer][z].model = invTranslation * rotation * translation * cubes[x][layer][z].model;
        }
    }
}

void RubikCube::swap_horizontal_matrix(int layer) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 / 2; j++) {
            std::swap(cubes[i][layer][j], cubes[i][layer][3 - j - 1]);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            std::swap(cubes[i][layer][j], cubes[j][layer][i]);
        }
    }
}

void RubikCube::rotate_vertical(int layer) {
    for (int y = 0; y < 3; ++y) {
        for (int z = 0; z < 3; ++z) {
            glm::vec3 center = glm::vec3(1.0f, 2.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(2.0f),
                                             glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                   -center); // Перемещаем в противоположную сторону от центра
            glm::mat4 invTranslation = glm::translate(glm::mat4(1.0f),
                                                      center); // Возвращаем кубики обратно после вращения
            cubes[layer][y][z].model = invTranslation * rotation * translation * cubes[layer][y][z].model;
        }
    }
}

void RubikCube::swap_vertical_matrix(int layer) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 / 2; j++) {
            std::swap(cubes[layer][i][j], cubes[layer][i][3 - j - 1]);
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            std::swap(cubes[layer][i][j], cubes[layer][j][i]);
        }
    }
}