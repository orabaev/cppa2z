#include <catch.hpp>
#include <tuple>
#include <string>
#include <array>
#include <unordered_map>

using namespace std;

TEST_CASE( "if", "[std] [modern] [if/switch initializers] [C++17]" ) {
    SECTION( "if" ) 
    {
        unordered_map<int, int> dic;
        if (auto [it, inserted] = dic.emplace(1, 10); inserted)
        {
            REQUIRE( inserted );    
        }
        else
        {
            REQUIRE( false );    
        }

        if (auto [it, inserted] = dic.emplace(1, 10); inserted)
        {
            REQUIRE( false );    
        }
        else
        {
            REQUIRE( !inserted );    
        }
    }
}

TEST_CASE( "switch", "[std] [modern] [if/switch initializers] [C++17]" ) {
    SECTION( "switch" ) 
    {
        auto mult = [](int i) {
            return i * 2;
        };   

        switch(int i = mult(3); i)
        {
            case 6:
                REQUIRE( i == 6 );
                break;
            default:
                REQUIRE( false );
        }
    }
}