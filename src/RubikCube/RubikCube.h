//
// Created by Timur on 23.04.2024.
//

#ifndef OPENGL_TUTORIAL_RUBIKCUBE_H
#define OPENGL_TUTORIAL_RUBIKCUBE_H

#include "../Cube/Cube.h"
#include <vector>
#include "../graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stack>

class RubikCube {
public:
    glm::vec3 right_center_coords;
    glm::vec3 front_center_coords;
    glm::vec3 up_center_coords;

    glm::vec3 up_vec;
    glm::vec3 front_vec;
    glm::vec3 right_vec;
    std::vector<std::vector<std::vector<Cube> > > cubes;
    std::vector<char> st;
    Shader *shader;

    RubikCube(Shader *shader);

    void draw();


    void make_grid();


    void draw_cube(int x, int y, int z);

    void rotate_horizontal(int layer, float angle);

    void swap_horizontal_matrix(int layer);

    void rotate_front(float angle);

    void rotate_back(float angle);

    void rotate_vertical(int layer, float angle);

    void swap_vertical_matrix(int layer);

    int load_from_file(const char *filename);

    void solve(float angle);

    void swap_vertical_matrix_front();

    void swap_vertical_matrix_back();

    void write_state(const char *fileName);


    void y_swap_cube();

    void y_backwards_swap_cube();

    void x_swap_cube();

    int white_center_id;
    int blue_center_id;
    int red_center_id;
    int green_center_id;
    int yellow_center_id;
    int orange_center_id;

    glm::vec3 find_cube_coords(int id);

    //actions
    void R();

    void R2();

    void R_back();

    void L();

    void L2();

    void L_back();

    void U();

    void U2();

    void U_back();


    void F();

    void F2();

    void F_back();

    void pif_paf();

    void left_pif_paf();

    void y();

    void y_back();

    //solve algorithms
    void white_to_up();

    void make_white_cross();

    void first_layer();

    void second_layer();

    void yellow_cross();

    void third_layer();

    void rebra();

    void make_corners();

};


#endif //OPENGL_TUTORIAL_RUBIKCUBE_H
