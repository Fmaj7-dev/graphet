#define GL_GLEXT_PROTOTYPES

#include "render/particlesystem.h"
#include "render/rendermanager.h"
#include "ui/windowmanager.h"
#include "graph/graph.h"

#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
   int width = 640;
   int height = 480;

   RenderManager rm (width, height);
   Graph graph(rm);
   WindowManager wm (width, height, &rm, &graph);

   wm.init( argc, argv );
   rm.init();

   
   graph.initRandom();

   wm.mainLoop();

   return 0;
}
