#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

TEST_CASE( "accumulate", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute sum of all elements in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5};

        const int sum = accumulate(cbegin(vec), cend(vec), 0);    
                  
        REQUIRE( 15 == sum  ); 
    } 

    SECTION( "compute product of all elements in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5};

        auto multiply = [](int x, int y) { return x * y; };
    
        const int product = accumulate(cbegin(vec), cend(vec), 1, multiply);    
                  
        REQUIRE( 120 == product  ); 
    } 

}

TEST_CASE( "adjacent_difference", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute dfference between next element and it previous element writing the result to a different range" ) {
        const vector<int>      vec{4, 9, 15, 22, 30};
              vector<int>   result;
        const vector<int> expected{4, 5,  6,  7,  8};

        adjacent_difference(cbegin(vec), cend(vec), back_inserter(result));    
                  
        REQUIRE( expected == result ); 
    } 

    SECTION( "compute absolute dfference between next element and it previous element writing the result to a different range" ) {
        const vector<int>      vec{4, -9, 15, -22, -30};
              vector<int>   result;
        const vector<int> expected{4,  5,  6,   7,   8};


        auto diff = [](int x, int y) { return abs(abs(x) - abs(y)); };

        adjacent_difference(cbegin(vec), cend(vec), back_inserter(result), diff);    
                  
        REQUIRE( expected == result ); 
    } 

}

TEST_CASE( "inner_product", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute sum(+) of products(*)" ) {
        const vector<int> vec1{1, 2, 3};
        const vector<int> vec2{4, 5, 6};
        
        constexpr int value = 10; 
        constexpr int expected = (1 * 4)  +  (2 * 5)  +  (3 * 6) + value;

        const int result = inner_product(
                                 cbegin(vec1)
                               , cend(vec1) 
                               , cbegin(vec2) 
                               , value
                           ); 
                  
        REQUIRE( expected == result ); 
    } 

    SECTION( "compute products(*) of sum(+)" ) {
        const vector<int> vec1{1, 2, 3};
        const vector<int> vec2{4, 5, 6};
        
        constexpr int value = 10; 
        constexpr int expected = (1 + 4)  *  (2 + 5)  *  (3 + 6) * value;

        auto op1 = [](int x, int y) { return x * y; };
        auto op2 = [](int x, int y) { return x + y; };

        const int result = inner_product(
                                 cbegin(vec1)
                               , cend(vec1) 
                               , cbegin(vec2) 
                               , value
                               , op1
                               , op2
                           ); 
                  
        REQUIRE( expected == result ); 
    }

}

