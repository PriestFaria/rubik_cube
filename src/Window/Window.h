//
// Created by Timur on 06.04.2024.
//

#ifndef OPENGL_TUTORIAL_WINDOW_H
#define OPENGL_TUTORIAL_WINDOW_H

class GLFWwindow;

class Window {
public:
    static int initialize(int width, int height, const char *title);

    static void terminate();

    static bool isShouldClose();

    static void setShouldClose(bool flag);

    static void swapBuffers();

    static GLFWwindow *window;
};

#endif //OPENGL_TUTORIAL_WINDOW_H
