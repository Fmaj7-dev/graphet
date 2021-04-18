//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "math/symmetric_matrix.hpp"

#include <iostream>

TEST_CASE("SymmetricMatrix")
{
    SymmetricMatrix matrix(5);
    matrix.reset(42);

    matrix.print();

    // check reset
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
        {
            if(i==j)
            {
                std::cout<<"getting "<<i<<" "<<j<<std::endl;
                REQUIRE( matrix.get(i, j) == 0 );
            }
            else
            {
                std::cout<<"getting "<<i<<" "<<j<<std::endl;
                REQUIRE( matrix.get(i, j) == 42 );
            }
        }
  }