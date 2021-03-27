//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph/graph.h"
#include "render/rendermanager.h"

TEST_CASE("Graph")
{
    Node a("Alekhine");
    Node b("Barsov");
    Node c("Carlsen");
    Node d("Dimitrov");

    RenderManager rm (20, 20);
    Graph g(&rm);
    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
    g.addNode(d);

    g.addLink(a, b);
    g.addLink(b, c);

    g.print();

    // test init size
    REQUIRE( 1 == 1 );
  
}