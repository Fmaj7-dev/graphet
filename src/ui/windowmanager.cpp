#include "windowmanager.h"

static WindowManager* wm;

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

WindowManager::WindowManager(int w, int h, RenderManager* rm)
: rm_(rm),
  width_(w),
  height_(h)
{
    wm = this;
}

void WindowManager::resize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void WindowManager::draw()
{
    rm_->draw();

    glutSwapBuffers();

}

void WindowManager::update()
{
    rm_->update();
    glutPostRedisplay();   
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
}

void WindowManager::mainLoop()
{
    glutMainLoop();
}