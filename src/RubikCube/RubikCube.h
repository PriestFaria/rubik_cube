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

class RubikCube {
public:
    std::vector<std::vector<std::vector<Cube> > > cubes;
    Shader *shader;

    RubikCube(Shader *shader);

    void draw();


    void make_grid();


    void draw_cube(int x, int y, int z);

    void rotate_horizontal(int layer);

    void swap_horizontal_matrix(int layer);

    void rotate_vertical(int layer);

    void swap_vertical_matrix(int layer);

};


#endif //OPENGL_TUTORIAL_RUBIKCUBE_H
