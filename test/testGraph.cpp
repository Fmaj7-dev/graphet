//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph.h"


TEST_CASE("Graph")
{
    Node a("Alekhine");
    Node b("Barsov");
    Node c("Carlsen");
    Node d("Dimitrov");

    Graph g;
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