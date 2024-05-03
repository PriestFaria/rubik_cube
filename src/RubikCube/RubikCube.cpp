//
// Created by Timur on 23.04.2024.
//

#include "RubikCube.h"
#include <fstream>
#include <iostream>
#include "../Window/Window.h"
#include <random>

RubikCube::RubikCube(Shader *shader) : shader(shader) {
    right_center_coords = glm::vec3(2, 1, 1);
    front_center_coords = glm::vec3(1, 1, 2);
    up_center_coords = glm::vec3(1, 2, 1);


    up_vec = glm::vec3(0, 1, 0);
    front_vec = glm::vec3(0, 0, 1);
    right_vec = glm::vec3(1, 0, 0);

    green_center_id = 5;
    orange_center_id = 11;
    blue_center_id = 23;
    yellow_center_id = 15;
    red_center_id = 17;
    white_center_id = 13;
    cubes = std::vector<std::vector<std::vector<Cube> > >(3, std::vector<std::vector<Cube> >(3, std::vector<Cube>(3,
                                                                                                                  Cube())));
    int id = 0;
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                ++id;
                cubes[x][y][z].x = x;
                cubes[x][y][z].y = y;
                cubes[x][y][z].z = z;
                cubes[x][y][z].id = id;
            }
        }
    }
    make_grid();
    st = std::vector<char>();
}


void RubikCube::rotate_front(float angle) {

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            glm::vec3 center = glm::vec3(2.0f, 2.0f, 1.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
                                             glm::vec3(0.0f, 0.0f, -1.0f));
            glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                   -center); // Перемещаем в противоположную сторону от центра
            glm::mat4 invTranslation = glm::translate(glm::mat4(1.0f),
                                                      center); // Возвращаем кубики обратно после вращения
            cubes[x][y][0].model = invTranslation * rotation * translation * cubes[x][y][0].model;
        }
    }

}

void RubikCube::swap_vertical_matrix_front() {
    glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    // Теперь нужно выполнить транспонирование матрицы, чтобы переставить элементы правильно
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            std::swap(cubes[i][j][0], cubes[j][i][0]);
        }
    }
    // Меняем местами элементы в каждой строке передней грани
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 / 2; ++j) {
            std::swap(cubes[i][j][0], cubes[i][3 - j - 1][0]);
        }
    }
    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec4 white_n_homogeneous = glm::vec4(cubes[x][z][0].white_n, 0.0f);
            glm::vec3 transformed_white_n = glm::vec3(rotationM * white_n_homogeneous);
            if (abs(transformed_white_n.x) < 1)
                transformed_white_n.x = 0.0f;
            if (abs(transformed_white_n.y) < 1)
                transformed_white_n.y = 0.0f;
            if (abs(transformed_white_n.z) < 1)
                transformed_white_n.z = 0.0f;


            if (transformed_white_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][0].white_n = transformed_white_n; // Обновляем вектор после вращения



            glm::vec4 blue_n_homogeneous = glm::vec4(cubes[x][z][0].blue_n, 0.0f);
            glm::vec3 transformed_blue_n = glm::vec3(rotationM * blue_n_homogeneous);
            if (abs(transformed_blue_n.x) < 1)
                transformed_blue_n.x = 0.0f;
            if (abs(transformed_blue_n.y) < 1)
                transformed_blue_n.y = 0.0f;
            if (abs(transformed_blue_n.z) < 1)
                transformed_blue_n.z = 0.0f;


            if (transformed_blue_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][0].blue_n = transformed_blue_n; // Обновляем вектор после вращения


            glm::vec4 red_n_homogeneous = glm::vec4(cubes[x][z][0].red_n, 0.0f);
            glm::vec3 transformed_red_n = glm::vec3(rotationM * red_n_homogeneous);
            if (abs(transformed_red_n.x) < 1)
                transformed_red_n.x = 0.0f;
            if (abs(transformed_red_n.y) < 1)
                transformed_red_n.y = 0.0f;
            if (abs(transformed_red_n.z) < 1)
                transformed_red_n.z = 0.0f;


            if (transformed_red_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][0].red_n = transformed_red_n; // Обновляем вектор после вращения

        }
    }
}


void RubikCube::rotate_back(float angle) {

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            glm::vec3 center = glm::vec3(2.0f, 2.0f, 1.0f); // Берем позицию (x, y, z) центрального кубика
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle),
                                             glm::vec3(0.0f, 0.0f, -1.0f));
            glm::mat4 translation = glm::translate(glm::mat4(1.0f),
                                                   -center); // Перемещаем в противоположную сторону от центра
            glm::mat4 invTranslation = glm::translate(glm::mat4(1.0f),
                                                      center); // Возвращаем кубики обратно после вращения
            cubes[x][y][2].model = invTranslation * rotation * translation * cubes[x][y][2].model;
        }
    }

}


void RubikCube::swap_vertical_matrix_back() {
    glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            std::swap(cubes[i][j][2], cubes[j][i][2]);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 / 2; j++) {
            std::swap(cubes[i][j][2], cubes[i][3 - j - 1][2]);
        }
    }
    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec4 white_n_homogeneous = glm::vec4(cubes[x][z][2].white_n, 0.0f);
            glm::vec3 transformed_white_n = glm::vec3(rotationM * white_n_homogeneous);
            if (abs(transformed_white_n.x) < 1)
                transformed_white_n.x = 0.0f;
            if (abs(transformed_white_n.y) < 1)
                transformed_white_n.y = 0.0f;
            if (abs(transformed_white_n.z) < 1)
                transformed_white_n.z = 0.0f;


            if (transformed_white_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][2].white_n = transformed_white_n; // Обновляем вектор после вращения



            glm::vec4 blue_n_homogeneous = glm::vec4(cubes[x][z][2].blue_n, 0.0f);
            glm::vec3 transformed_blue_n = glm::vec3(rotationM * blue_n_homogeneous);
            if (abs(transformed_blue_n.x) < 1)
                transformed_blue_n.x = 0.0f;
            if (abs(transformed_blue_n.y) < 1)
                transformed_blue_n.y = 0.0f;
            if (abs(transformed_blue_n.z) < 1)
                transformed_blue_n.z = 0.0f;


            if (transformed_blue_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][2].blue_n = transformed_blue_n; // Обновляем вектор после вращения


            glm::vec4 red_n_homogeneous = glm::vec4(cubes[x][z][2].red_n, 0.0f);
            glm::vec3 transformed_red_n = glm::vec3(rotationM * red_n_homogeneous);
            if (abs(transformed_red_n.x) < 1)
                transformed_red_n.x = 0.0f;
            if (abs(transformed_red_n.y) < 1)
                transformed_red_n.y = 0.0f;
            if (abs(transformed_red_n.z) < 1)
                transformed_red_n.z = 0.0f;


            if (transformed_red_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][z][2].red_n = transformed_red_n; // Обновляем вектор после вращения
        }
    }
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
            glm::mat3 rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f),
                                              glm::vec3(0.0f, -1.0f, 0.0f));
            cubes[x][layer][z].model = invTranslation * rotation * translation * cubes[x][layer][z].model;
        }
    }
}

void RubikCube::swap_horizontal_matrix(int layer) {
    glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));


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

    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec4 blue_n_homogeneous = glm::vec4(cubes[x][layer][z].blue_n, 0.0f);
            glm::vec3 transformed_blue_n = glm::vec3(rotationM * blue_n_homogeneous);

            if (abs(transformed_blue_n.x) < 1)
                transformed_blue_n.x = 0.0f;
            if (abs(transformed_blue_n.y) < 1)
                transformed_blue_n.y = 0.0f;
            if (abs(transformed_blue_n.z) < 1)
                transformed_blue_n.z = 0.0f;

            if (transformed_blue_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][layer][z].blue_n = transformed_blue_n; // Обновляем вектор после вращения


            glm::vec4 white_n_homogeneous = glm::vec4(cubes[x][layer][z].white_n, 0.0f);
            glm::vec3 transformed_white_n = glm::vec3(rotationM * white_n_homogeneous);
            if (abs(transformed_white_n.x) < 1)
                transformed_white_n.x = 0.0f;
            if (abs(transformed_white_n.y) < 1)
                transformed_white_n.y = 0.0f;
            if (abs(transformed_white_n.z) < 1)
                transformed_white_n.z = 0.0f;

            if (transformed_white_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][layer][z].white_n = transformed_white_n; // Обновляем вектор после вращения



            glm::vec4 red_n_homogeneous = glm::vec4(cubes[x][layer][z].red_n, 0.0f);
            glm::vec3 transformed_red_n = glm::vec3(rotationM * red_n_homogeneous);
            if (abs(transformed_red_n.x) < 1)
                transformed_red_n.x = 0.0f;
            if (abs(transformed_red_n.y) < 1)
                transformed_red_n.y = 0.0f;
            if (abs(transformed_red_n.z) < 1)
                transformed_red_n.z = 0.0f;

            if (transformed_red_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[x][layer][z].red_n = transformed_red_n; // Обновляем вектор после вращения

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
    glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


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
    for (int x = 0; x < 3; ++x) {
        for (int z = 0; z < 3; ++z) {
            glm::vec4 white_n_homogeneous = glm::vec4(cubes[layer][x][z].white_n, 0.0f);
            glm::vec3 transformed_white_n = glm::vec3(rotationM * white_n_homogeneous);
            if (abs(transformed_white_n.x) < 1)
                transformed_white_n.x = 0.0f;
            if (abs(transformed_white_n.y) < 1)
                transformed_white_n.y = 0.0f;
            if (abs(transformed_white_n.z) < 1)
                transformed_white_n.z = 0.0f;


            if (transformed_white_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[layer][x][z].white_n = transformed_white_n; // Обновляем вектор после вращения



            glm::vec4 blue_n_homogeneous = glm::vec4(cubes[layer][x][z].blue_n, 0.0f);
            glm::vec3 transformed_blue_n = glm::vec3(rotationM * blue_n_homogeneous);
            if (abs(transformed_blue_n.x) < 1)
                transformed_blue_n.x = 0.0f;
            if (abs(transformed_blue_n.y) < 1)
                transformed_blue_n.y = 0.0f;
            if (abs(transformed_blue_n.z) < 1)
                transformed_blue_n.z = 0.0f;


            if (transformed_blue_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[layer][x][z].blue_n = transformed_blue_n; // Обновляем вектор после вращения


            glm::vec4 red_n_homogeneous = glm::vec4(cubes[layer][x][z].red_n, 0.0f);
            glm::vec3 transformed_red_n = glm::vec3(rotationM * red_n_homogeneous);
            if (abs(transformed_red_n.x) < 1)
                transformed_red_n.x = 0.0f;
            if (abs(transformed_red_n.y) < 1)
                transformed_red_n.y = 0.0f;
            if (abs(transformed_red_n.z) < 1)
                transformed_red_n.z = 0.0f;


            if (transformed_red_n != glm::vec3(0.0f, 0.0f, 0.0f))
                cubes[layer][x][z].red_n = transformed_red_n; // Обновляем вектор после вращения



        }
    }

}


int RubikCube::load_from_file(const char *filename) {

    std::string line;
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        in.close();
        return 1;
    }
    if (in.is_open()) {
        solve(90.0f);
        st.erase(st.begin(), st.end());
        while (std::getline(in, line)) {
            if (line[0] == '1') {
                //верх
                rotate_horizontal(2, 90.0f);
                swap_horizontal_matrix(2);
                st.push_back('1');
            }
            if (line[0] == '2') {
                //передняя
                rotate_front(90.0f);
                swap_vertical_matrix_front();
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
                //задняя грань
                rotate_back(90.0f);
                swap_vertical_matrix_back();
                st.push_back('5');
            }
            if (line[0] == '6') {
                //право
                rotate_vertical(0, 90.0f);
                swap_vertical_matrix(0);
                st.push_back('6');
            }

        }
        in.close();
    }
    std::cout << "Loaded state from file: " << filename << std::endl;
    return 0;
}

void RubikCube::solve(float angle) {
//    left_pif_paf();
    white_to_up();
    while (make_white_cross());
    make_perfect_cross();
    first_layer();
    second_layer();
    yellow_cross();
    third_layer();
    rebra();
    make_corners();
}

void RubikCube::write_state(const char *fileName) {
    std::ofstream in;
    in.open(fileName);

    for (auto k: st) {
        in << k << std::endl;
    }
    std::cout << "Written state to file: " << fileName << std::endl;
}


void RubikCube::y_swap_cube() {
    for (int i = 0; i < 3; ++i) {
        rotate_horizontal(0, 30);
        rotate_horizontal(2, 30);
        rotate_horizontal(1, 30);

        draw();
        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_horizontal_matrix(0);

    swap_horizontal_matrix(2);

    swap_horizontal_matrix(1);
}


void RubikCube::y_backwards_swap_cube() {
    for (int i = 0; i < 3; ++i) {
        y_swap_cube();
    }
};

void RubikCube::x_swap_cube() {
    for (int i = 0; i < 3; ++i) {
        rotate_vertical(2, 30.0f);
        rotate_vertical(1, 30.0f);
        rotate_vertical(0, 30.0f);

        draw();

        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix(2);


    swap_vertical_matrix(1);

    swap_vertical_matrix(0);
}

glm::vec3 RubikCube::find_cube_coords(int id) {
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                if (cubes[x][y][z].id == id)
                    return glm::vec3(x, y, z);
            }
        }
    }
}

void RubikCube::white_to_up() {
    int i = 0;
    while (find_cube_coords(white_center_id) != up_center_coords) {
        x_swap_cube();
        if (i % 3 == 0) {
            y_swap_cube();
        }
        ++i;
    }
}

void RubikCube::R() {
    for (int i = 0; i < 3; ++i) {
        rotate_vertical(2, 30.0f);
        draw();

        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix(2);
    for (int i = 0; i < 3; ++i) {
        rotate_vertical(2, 30.0f);
        draw();

        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix(2);
    for (int i = 0; i < 3; ++i) {
        rotate_vertical(2, 30.0f);
        draw();

        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix(2);
}

void RubikCube::R2() {
    R();
    R();
}

void RubikCube::R_back() {
    R();
    R();
    R();
}

void RubikCube::L() {
    for (int i = 0; i < 3; ++i) {
        rotate_vertical(0, 30.0f);
        draw();
        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix(0);
}

void RubikCube::L2() {
    L();
    L();
}

void RubikCube::L_back() {
    L();
    L();
    L();
}

void RubikCube::U() {
    for (int i = 0; i < 3; ++i) {
        rotate_horizontal(2, 30.0f);

        draw();
        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_horizontal_matrix(2);
}

void RubikCube::U2() {
    U();
    U();
}

void RubikCube::U_back() {
    U();
    U();
    U();
}

void RubikCube::F() {
    for (int i = 0; i < 3; ++i) {
        rotate_back(30.0f);
        draw();

        Window::swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    swap_vertical_matrix_back();
}

void RubikCube::F2() {
    F();
    F();
}


void RubikCube::F_back() {
    F();
    F();
    F();
}


void RubikCube::pif_paf() {
    R();
    U();
    R_back();
    U_back();
}

void RubikCube::left_pif_paf() {
    L_back();
    U_back();
    L();
    U();
}

void RubikCube::y() {
    y_swap_cube();
}

void RubikCube::y_back() {
    y_backwards_swap_cube();
}

int RubikCube::make_white_cross() {
    int i = 0;
    int r = 0;
    while (cubes[0][2][1].white_n != up_vec || cubes[1][2][0].white_n != up_vec || cubes[1][2][2].white_n != up_vec ||
           cubes[2][2][1].white_n != up_vec) {
        white_to_up();
        y();
        ++i;

        //white-green
        //1 случай
        if (cubes[2][1][2].white_n == front_vec && cubes[2][1][2].white_n != up_vec) {
            R();
            r = 0;
        }
        //2 случай
        if (cubes[0][1][2].white_n == front_vec && cubes[0][2][1].white_n != up_vec) {
            L_back();
            r = 0;
        }
        //3 случай
        if (cubes[2][1][2].white_n == front_vec && cubes[2][2][1].white_n == up_vec) {
            if (i % 3 == 0) {
                U();
                R();
            }
            if (i % 3 == 1) {
                U_back();
                R();
            }
            if (i % 3 == 2) {
                U2();
                R();
            }
            r = 0;
        }
        //4 случай
        if (cubes[0][1][2].white_n == front_vec && cubes[0][2][1].white_n == up_vec) {
            if (i % 3 == 0) {
                U();
                L_back();
            }
            if (i % 3 == 1) {
                U_back();
                L_back();
            }
            if (i % 3 == 2) {
                U2();
                L_back();
            }
            r = 0;
        }
        //5 случай
        if (cubes[1][2][2].white_n == front_vec) {
            if (i % 2 == 1) {
                F_back();
                L_back();
            } else {
                F();
                R();
            }
            r = 0;
        }
        //6 случай
        if (cubes[1][0][2].white_n == front_vec) {
            if (i % 2 == 1) {
                F_back();
                R();
            } else {
                F();
                L_back();
            }
            r = 0;
        }
        //7 случай
        if (cubes[1][0][2].white_n == -up_vec) {
            F2();
            r++;
            //разборка при зацикливании
            if (r >= 10) {
                pif_paf();
                F();
                R();
                F2();
                U();
                r = 0;
            }
        }

    }
    int m = 0;
    while (true) {
        ++m;
        int k = 0;
        // Проверка совпадения цветов краевых кубиков с цветом средних кубиков соответствующих граней
        if (cubes[1][1][2].get_color_by_n(front_vec) == cubes[1][2][2].get_color_by_n(front_vec)) {
            std::cout << cubes[1][1][2].get_color_by_n(front_vec) << std::endl;
            ++k;
        }
        if (cubes[2][1][1].get_color_by_n(right_vec) == cubes[2][2][1].get_color_by_n(right_vec)) {
            std::cout << cubes[2][1][1].get_color_by_n(right_vec) << std::endl;
            ++k;
        }
        if (cubes[1][1][0].get_color_by_n(-front_vec) == cubes[1][2][0].get_color_by_n(-front_vec)) {
            std::cout << cubes[1][1][0].get_color_by_n(-front_vec) << std::endl;

            ++k;
        }
        if (cubes[0][1][1].get_color_by_n(-right_vec) == cubes[0][2][1].get_color_by_n(-right_vec)) {
            std::cout << cubes[0][1][1].get_color_by_n(-right_vec) << std::endl;
            ++k;
        }
        if (k >= 2) {
            break;
        }
        U(); // Вращаем верхнюю грань, чтобы выровнять крест с центрами
    }
    return 0;
}


void RubikCube::make_perfect_cross() {
    while (true) {
        int f1 = 0;
        for (int i = 0; i < 4; ++i) {
            y();
            if (cubes[2][2][1].get_color_by_n(right_vec) == cubes[1][1][0].get_color_by_n(-front_vec)) {
                pif_paf();
                R();
                f1 = 1;
            }
            if (cubes[2][2][1].get_color_by_n(right_vec) == cubes[0][1][1].get_color_by_n(-right_vec)) {
                pif_paf();
                R();
                f1 = 1;
            }
        }

        if (f1 == 0)
            break;
    }
}

void RubikCube::pif_paf_back() {
    U();
    R();
    U_back();
    R_back();
}

void RubikCube::first_layer() {
    x_swap_cube();
    x_swap_cube();
//    for (int i = 0; i < 4; ++i) {
//        y();
//        if (cubes[2][2][2].white_n == right_vec) {
//            for (int k = 0; k < 4; ++k) {
//                if (cubes[2][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec)
//                    && cubes[2][2][2].get_color_by_n(up_vec) == cubes[2][1][1].get_color_by_n(right_vec)) {
//                    pif_paf();
//                    break;
//                } else {
//                    std::cout << "1" << std::endl;
//                    U_back();
//                    y();
//                }
//            }
//        }
//        if (cubes[2][2][2].white_n == front_vec) {
//            for (int k = 0; k < 4; ++k) {
//                if (cubes[2][2][2].get_color_by_n(up_vec) == cubes[1][1][2].get_color_by_n(front_vec)
//                    && cubes[2][2][2].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec)) {
//                    pif_paf_back();
//                    break;
//                } else {
//                    std::cout << "3" << std::endl;
//                    U();
//                    y_back();
//                }
//            }
//        }
//        if (cubes[2][2][2].white_n == up_vec) {
//            for (int k = 0; k < 4; ++k) {
//                if (cubes[2][2][2].get_color_by_n(right_vec) == cubes[1][1][2].get_color_by_n(front_vec)
//                    && cubes[2][2][2].get_color_by_n(front_vec) == cubes[2][1][1].get_color_by_n(right_vec)) {
//                    pif_paf();
//                    pif_paf();
//                    pif_paf();
//                    break;
//                } else {
//                    std::cout << "3" << std::endl;
//                    U();
//                    y_back();
//                }
//            }
//
//        }
//    }
    int i = 0;
    int f = 0;
    for (int h = 0; h < 10; ++h) {
        y();
        if (cubes[2][2][2].white_n == right_vec) {
            for (int k = 0; k < 4; ++k) {
                if (cubes[2][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
                    cubes[1][1][2].get_color_by_n(front_vec) ==
                    cubes[1][0][2].get_color_by_n(front_vec) &&
                    cubes[2][2][2].get_color_by_n(up_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                    cubes[2][1][1].get_color_by_n(right_vec) ==
                    cubes[2][0][1].get_color_by_n(right_vec)) {
                    pif_paf();
                }
                std::cout << "1" << std::endl;
                U();
                y_back();
            }
        }
        if (cubes[2][2][2].white_n == up_vec) {
            for (int k = 0; k < 4; ++k) {
                if (cubes[2][2][2].get_color_by_n(right_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
                    cubes[1][1][2].get_color_by_n(front_vec) ==
                    cubes[1][0][2].get_color_by_n(front_vec) &&
                    cubes[2][2][2].get_color_by_n(front_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                    cubes[2][1][1].get_color_by_n(right_vec) ==
                    cubes[2][0][1].get_color_by_n(right_vec)) {
                    f = 1;
                    pif_paf();
                    pif_paf();
                    pif_paf();
                }
                std::cout << "2" << std::endl;
                U();
                y_back();
            }
        }
        if (cubes[2][2][2].white_n == front_vec) {
            for (int k = 0; k < 4; ++k) {
                if (cubes[2][2][2].get_color_by_n(up_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
                    cubes[1][1][2].get_color_by_n(front_vec) ==
                    cubes[1][0][2].get_color_by_n(front_vec) &&
                    cubes[2][2][2].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                    cubes[2][1][1].get_color_by_n(right_vec) ==
                    cubes[2][0][1].get_color_by_n(right_vec)) {
                    pif_paf();
                    pif_paf();
                    pif_paf();
                    pif_paf();
                    pif_paf();
                    f = 1;

                }
                std::cout << "3" << std::endl;
                U();
                y_back();
            }
        }
        if (cubes[2][0][2].white_n == front_vec || cubes[2][0][2].white_n == right_vec ||
            (cubes[2][0][2].white_n == -up_vec &&
             cubes[2][0][2].get_color_by_n(front_vec) != cubes[1][1][2].get_color_by_n(front_vec) &&
             cubes[2][0][2].get_color_by_n(right_vec) != cubes[2][1][1].get_color_by_n(right_vec))) {
            std::cout << "4" << std::endl;
            pif_paf();
            f = 1;
        }

    }
}

void RubikCube::second_layer() {
    int k = 0;
    //не соединяю ребро с центром — ИСПРАВИТЬ
    int found = 0;
    while (true) {
        int f = 0;
        if (found) {
            U();
            y_back();
        } else {
            y();
        }
        if (cubes[1][2][2].yellow_n() != up_vec && cubes[1][2][2].yellow_n() != front_vec &&
            cubes[1][2][2].white_n != up_vec && cubes[1][2][2].white_n != front_vec) {
            found = 1;
        }
        if (cubes[1][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
            cubes[1][2][2].get_color_by_n(up_vec) != cubes[2][1][1].get_color_by_n(right_vec) &&
            cubes[1][2][2].yellow_n() != up_vec && cubes[1][2][2].yellow_n() != front_vec) {
            std::cout << 1 << std::endl;
            U_back();
            left_pif_paf();
            y_back();
            pif_paf();
            f = 1;
            k = 0;
            found = 0;
        }
        if (cubes[1][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
            cubes[1][2][2].get_color_by_n(up_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
            cubes[1][2][2].yellow_n() != up_vec && cubes[1][2][2].yellow_n() != front_vec) {
            std::cout << 2 << std::endl;
            U();
            pif_paf();
            y();
            left_pif_paf();
            f = 1;
            k = 0;
            found = 0;
        }
        if (cubes[2][1][2].get_color_by_n(front_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
            cubes[2][1][2].get_color_by_n(right_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
            cubes[2][1][2].yellow_n() != right_vec) {
            std::cout << 3 << std::endl;
            pif_paf();
            y();
            left_pif_paf();
            found = 0;
            f = 1;
            k = 0;

        }
        if (cubes[1][1][2].get_color_by_n(front_vec) != cubes[2][1][2].get_color_by_n(front_vec)
            && cubes[2][1][2].get_color_by_n(front_vec) == cubes[2][1][1].get_color_by_n(right_vec)
            && cubes[2][1][2].get_color_by_n(right_vec) != cubes[1][1][2].get_color_by_n(front_vec) &&
            cubes[2][1][2].yellow_n() != right_vec) {
            std::cout << 4 << std::endl;
            pif_paf();
            y();
            left_pif_paf();
            f = 1;
            k = 0;
            found = 0;
        }
        if (f == 0) {
            k++;
            if (k == 32)
                break;
        }
    }

}

void RubikCube::yellow_cross() {
    while (!(cubes[1][2][0].yellow_n() == up_vec && cubes[1][2][1].yellow_n() == up_vec &&
             cubes[0][2][1].yellow_n() == up_vec && cubes[2][2][1].yellow_n() == up_vec &&
             cubes[1][2][2].yellow_n() == up_vec)) {
        y();
        if (cubes[1][2][0].yellow_n() == up_vec && cubes[0][2][1].yellow_n() == up_vec &&
            cubes[1][2][1].yellow_n() == up_vec && cubes[2][2][1].yellow_n() != up_vec &&
            cubes[1][2][2].yellow_n() != up_vec) {
            F();
            pif_paf();
            pif_paf();
            F_back();
        }
        if (cubes[0][2][1].yellow_n() == up_vec && cubes[1][2][1].yellow_n() == up_vec &&
            cubes[2][2][1].yellow_n() == up_vec
            && cubes[1][2][0].yellow_n() != up_vec && cubes[1][2][2].yellow_n() != up_vec) {
            F();
            pif_paf();
            F_back();
        }
        if (cubes[1][2][0].yellow_n() != up_vec && cubes[1][2][1].yellow_n() == up_vec &&
            cubes[0][2][1].yellow_n() != up_vec && cubes[2][2][1].yellow_n() != up_vec &&
            cubes[1][2][2].yellow_n() != up_vec) {
            F();
            pif_paf();
            F_back();

            U2();

            F();
            pif_paf();
            pif_paf();
            F_back();
        }
    }
}

void RubikCube::third_layer() {
    std::cout << "THIRD LAYER\n";
    x_swap_cube();
    y();
    while (!(cubes[0][2][0].yellow_n() == -right_vec && cubes[0][0][0].yellow_n() == -right_vec &&
             cubes[0][2][2].yellow_n() == -right_vec && cubes[0][0][2].yellow_n() == -right_vec)) {
        L();
        if (cubes[0][2][0].yellow_n() == up_vec) {
            pif_paf();
            pif_paf();
            pif_paf();
            pif_paf();
        }
        if (cubes[0][2][0].yellow_n() == -front_vec) {
            pif_paf();
            pif_paf();
        }
    }
}

void RubikCube::rebra() {
    std::cout << "REBRA\n";
    y();
    x_swap_cube();
    int k = 0;
    while (!(cubes[2][2][1].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
             cubes[1][2][0].get_color_by_n(-front_vec) == cubes[1][1][0].get_color_by_n(-front_vec) &&
             cubes[0][2][1].get_color_by_n(-right_vec) == cubes[0][1][1].get_color_by_n(-right_vec) &&
             cubes[1][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec))) {
        U();
        y_back();
        if (cubes[1][2][0].get_color_by_n(-front_vec) == cubes[1][1][0].get_color_by_n(-front_vec) &&
            cubes[0][2][1].get_color_by_n(-right_vec) == cubes[0][1][1].get_color_by_n(-right_vec)) {
            R();
            U();
            R_back();
            F_back();
            R();
            U();
            R_back();
            U_back();
            R_back();
            F();
            R2();
            U_back();
            R_back();
            U_back();
            k = 0;
        }
        if (cubes[1][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
            cubes[1][2][0].get_color_by_n(-front_vec) == cubes[1][1][0].get_color_by_n(-front_vec)) {
            R();
            U();
            R_back();
            F_back();
            R();
            U();
            R_back();
            U_back();
            R_back();
            F();
            R2();
            U_back();
            R_back();
            U_back();

            U2();

            R();
            U();
            R_back();
            F_back();
            R();
            U();
            R_back();
            U_back();
            R_back();
            F();
            R2();
            U_back();
            R_back();
            U_back();

            U_back();
            k = 0;
        }
        y();
        ++k;
        if (k == 16)
            break;
    }

}

bool RubikCube::check_if_up_solved() {
    int fl = 1;
    for (int i = 0; i < 4; ++i) {
        if (!(
                cubes[2][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
                cubes[2][2][2].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                cubes[2][2][2].get_color_by_n(up_vec) == cubes[1][2][1].get_color_by_n(up_vec) &&

                cubes[2][2][1].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                cubes[2][2][1].get_color_by_n(up_vec) == cubes[1][2][1].get_color_by_n(up_vec) &&

                cubes[2][2][0].get_color_by_n(up_vec) == cubes[1][2][1].get_color_by_n(up_vec) &&
                cubes[2][2][0].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec) &&
                cubes[2][2][0].get_color_by_n(-front_vec) == cubes[1][1][0].get_color_by_n(-front_vec)
        )) {
            fl = 0;
        }
    }
    return fl;
}


void RubikCube::make_corners() {
    while (!check_if_up_solved()) {
        int fl = 0;
        for (int i = 0; i < 4; ++i) {
            y();
            if (cubes[2][2][2].get_color_by_n(front_vec) == cubes[1][1][2].get_color_by_n(front_vec) &&
                cubes[2][2][2].get_color_by_n(right_vec) == cubes[2][1][1].get_color_by_n(right_vec)) {
                std::cout << "MAKE CORNERS" << std::endl;
                y();
                y();
                x_swap_cube();
                y();
                x_swap_cube();
                x_swap_cube();
                x_swap_cube();


                U2();
                R();
                U2();
                R_back();
                F2();
                U2();
                L_back();
                U2();
                L();
                F2();

                y();
                x_swap_cube();
                fl = 1;
                break;
            }
        }
        if (!fl) {
            std::cout << "MAKE CORNERS 2" << std::endl;
            y();
            y();
            x_swap_cube();
            y();
            x_swap_cube();
            x_swap_cube();
            x_swap_cube();


            U2();
            R();
            U2();
            R_back();
            F2();
            U2();
            L_back();
            U2();
            L();
            F2();
            y();
            x_swap_cube();
        }
    }
}


//горизонтальные
//1 - верхняя
//2 - передняя
//3 - нижняя
//вертикальные
//4 - левая
//5 - задняя
//6 - правая
