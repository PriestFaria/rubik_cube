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

    int load_from_file(const char* filename);

    void solve(float angle);

    void swap_vertical_matrix_front();

    void swap_vertical_matrix_back();

    void write_state(const char* fileName);

};


#endif //OPENGL_TUTORIAL_RUBIKCUBE_H
