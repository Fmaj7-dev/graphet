#define GL_GLEXT_PROTOTYPES

#include "particlesystem.h"
#include "rendermanager.h"
#include "windowmanager.h"

#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
   int width = 400;
   int height = 300;

   RenderManager rm (width, height);
   WindowManager wm (width, height, &rm);

   wm.init( argc, argv );
   rm.init();

   wm.mainLoop();

   return 0;
}
