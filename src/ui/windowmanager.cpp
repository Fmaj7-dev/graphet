#include "windowmanager.h"

#include "render/rendermanager.h"
#include "graph/graph.h"

#include <iostream>

static WindowManager* wm;

// global glut functions
void resize_global(int width, int height)
{
   wm->resize( width, height );
}

void draw_global()
{
   wm->draw();
}

void update_global()
{
   wm->update();
}

void keyboard_global(unsigned char key, int x, int y)
{
    wm->keyboard(key, x, y);
}

void keyboardup_global(unsigned char key, int x, int y)
{
    wm->keyboardUp(key, x, y);
}

void mouse_global(int button, int state, int x, int y)
{
    wm->mouse(button, state, x, y);
}

void motion_global(int x, int y)
{
    wm->motion(x, y);
}

void special_global(int key, int x, int y)
{
    wm->special(key, x, y);
}

WindowManager::WindowManager(int w, int h, RenderManager* rm, Graph* graph)
: rm_(rm),
  graph_(graph),
  width_(w),
  height_(h)
{
    wm = this;
    memset(keys, 0, 256);
    memset(buttons, 0, 3);
}

void WindowManager::resize(int w, int h)
{
    width_ = w;
    height_ = h;

    rm_->resize(w, h);
}

void WindowManager::draw()
{
    rm_->draw();

    glutSwapBuffers();

}

void WindowManager::update()
{
    if (keys[(unsigned char)'w'])
        rm_->moveForward();
    else if (keys[(unsigned char)'s'])
        rm_->moveBackward();
    else if (keys[(unsigned char)'a'])
        rm_->moveLeft();
    else if (keys[(unsigned char)'d'])
        rm_->moveRight();


    rm_->update();
    graph_->update();
    
    glutPostRedisplay();   
}

void WindowManager::keyboard(unsigned char key, int x, int y)
{
    keys[key] = true;
    std::cout<<"down "<<key<<" "<<x<<" "<<y<<std::endl;
}

void WindowManager::keyboardUp(unsigned char key, int x, int y)
{
    keys[key] = false;
    std::cout<<"up "<<key<<" "<<x<<" "<<y<<std::endl;
}

void WindowManager::mouse(int button, int state, int x, int y)
{
    std::cout<<"mouse "<<button<<" "<<state<<" "<<x<<" "<<y<<std::endl;
}

void WindowManager::motion(int x, int y)
{
    std::cout<<"motion "<<x<<" "<<y<<std::endl;
}

void WindowManager::special(int key, int x, int y)
{
    std::cout<<"special "<<key<<" "<<x<<" "<<y<<std::endl;
}

void WindowManager::init(int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitWindowSize( width_, height_ );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    glutCreateWindow( "graphs" );

    glutReshapeFunc( resize_global );
    glutDisplayFunc( draw_global );
    glutIdleFunc( update_global );
    glutKeyboardFunc( keyboard_global );
    glutKeyboardUpFunc( keyboardup_global );
    glutMouseFunc( mouse_global );
    glutMotionFunc( motion_global );
    glutSpecialFunc( special_global );

    #ifdef __APPLE__
        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    #endif
}

void WindowManager::mainLoop()
{
    glutMainLoop();

}