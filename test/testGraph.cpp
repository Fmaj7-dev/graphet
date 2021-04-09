//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph/graph.h"
#include "render/rendermanager.h"
#include "ui/windowmanager.h"

TEST_CASE("Graph")
{
    Node a("Alekhine");
    Node b("Barsov");
    Node c("Carlsen");
    Node d("Dimitrov");

    RenderManager rm ( 640, 480 );
    Graph graph( &rm );
    WindowManager wm (640, 480, &rm, &graph );

    wm.init( 0, nullptr );
    rm.init();

    graph.initRandom();
    
    graph.print();

    // test init size
    REQUIRE( 1 == 1 );
  
}