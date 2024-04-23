//
// Created by Timur on 23.04.2024.
//

#include "RubikCube.h"
#include <fstream>
#include "../Window/Window.h"

RubikCube::RubikCube(Shader *shader) : shader(shader) {
    cubes = std::vector<std::vector<std::vector<Cube> > >(3, std::vector<std::vector<Cube> >(3, std::vector<Cube>(3,
                                                                                                                  Cube())));
    make_grid();
    st = std::vector<char>();
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

void RubikCube::rotate_horizontal(int layer, float angle) {
    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec3 center = glm::vec3(2.0f, 3.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
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

void RubikCube::rotate_vertical(int layer, float angle) {
    for (int y = 0; y < 3; ++y) {
        for (int z = 0; z < 3; ++z) {
            glm::vec3 center = glm::vec3(1.0f, 2.0f, 2.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
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


void RubikCube::load_from_file(const char *filename) {
    std::string line;

    std::ifstream in(filename);
    if (in.is_open()) {
        while (std::getline(in, line)) {
            if (line[0] == '1') {
                //верх
                rotate_horizontal(2, 90.0f);
                swap_horizontal_matrix(2);
                st.push_back('1');
            }
            if (line[0] == '2') {
                //средняя горизонтальная
                rotate_horizontal(1, 90.0f);
                swap_horizontal_matrix(1);
                st.push_back('2');
            }
            if (line[0] == '3') {
                //низ
                rotate_horizontal(0, 90.0f);
                swap_horizontal_matrix(0);
                st.push_back('3');
            }
            if (line[0] == '4') {
                //лево
                rotate_vertical(2, 90.0f);
                swap_vertical_matrix(2);
                st.push_back('4');
            }
            if (line[0] == '5') {
                //средняя вертикальная
                rotate_vertical(1, 90.0f);
                swap_vertical_matrix(1);
                st.push_back('5');
            }
            if (line[0] == '6') {
                //право
                rotate_vertical(2, 90.0f);
                swap_vertical_matrix(2);
                st.push_back('6');
            }

        }
    }
    in.close();
}

void RubikCube::solve(float angle) {
    std::vector<char> reversedSt(st.rbegin(), st.rend());
    for (auto k: reversedSt) {
        if (k == '1') {
            //верх
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_horizontal(2, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }

                swap_horizontal_matrix(2);
            }
        }
        if (k == '2') {
            //средняя горизонтальная
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_horizontal(1, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                swap_horizontal_matrix(1);
            }
        }
        if (k == '3') {
            //низ
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_horizontal(0, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                swap_horizontal_matrix(0);
            }
        }
        if (k == '4') {
            //лево
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_vertical(2, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                swap_vertical_matrix(2);
            }
        }
        if (k == '5') {
            //средняя вертикальная
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_vertical(1, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                swap_vertical_matrix(1);
            }
        }
        if (k == '6') {
            //право
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 90/angle; ++i) {
                    rotate_vertical(2, angle);
                    draw();
                    Window::swapBuffers();
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }
                swap_vertical_matrix(2);
            }
        }
    }
}