#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

class RenderManager;
class Graph;

class WindowManager
{
public:
    WindowManager(int w, int h, RenderManager* rm, Graph* graph);

    void resize(int w, int h);

    void draw();

    void update();

    void keyboard(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);

    void mouse(int button, int state, int x, int y);

    void motion(int x, int y);

    void special(int key, int x, int y);

    void init(int argc, char *argv[]);

    void mainLoop();

private:

    RenderManager* rm_;
    Graph* graph_;

    int width_;
    int height_;
};

#endif