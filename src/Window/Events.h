//
// Created by Timur on 06.04.2024.
//

#ifndef OPENGL_TUTORIAL_EVENTS_H
#define OPENGL_TUTORIAL_EVENTS_H

#include "Window.h"

class Events {
public:
    static bool *keys;
    static unsigned int *frames;
    static unsigned int current;
    static float dX;
    static float dY;
    static float x;
    static float y;
    static bool cursor_locked;
    static bool cursor_started;

    static int initialize();

    static void pullEvents();

    static bool pressed(int keycode);
    static bool jpressed(int keycode);

    static bool clicked(int button);
    static bool jclicked(int button);

    static void toggleCursor();
};


#endif //OPENGL_TUTORIAL_EVENTS_H
