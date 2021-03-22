#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "rendermanager.h"

class WindowManager
{
public:
    WindowManager(int w, int h, RenderManager* rm);

    void resize(int w, int h);

    void draw();

    void update();

    void init(int argc, char *argv[]);

    void mainLoop();

private:

    RenderManager* rm_;

    int width_;
    int height_;
};

#endif