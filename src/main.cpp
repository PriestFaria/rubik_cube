#include "glew.h"
#include <GLFW/glfw3.h>
#include "Window/Events.h"
#include "Window/Window.h"
int WIDTH = 1280;
int HEIGHT = 720;

int main(void) {
    Window::initialize(WIDTH, HEIGHT, "Window 2");
    Events::initialize();

    while(!Window::isShouldClose()){
        Events::pullEvents();
        if(Events::jpressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if(Events::jclicked(GLFW_MOUSE_BUTTON_1)){
            glClearColor(1, 0, 0, 1);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        Window::swapBuffers();

    }
    return 0;
}


