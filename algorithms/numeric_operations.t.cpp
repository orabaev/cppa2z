#include <catch.hpp>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

using namespace std;

TEST_CASE( "accumulate", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute sum of all elements in the range plus the initial value" ) {
        const vector<int> vec{1, 2, 3};

        const int initial_value = 10; 
        const int expected = initial_value + 1 + 2 + 3;

        const int sum = accumulate(cbegin(vec), cend(vec), initial_value);    
                  
        REQUIRE( sum == expected ); 
    } 

    SECTION( "compute product of all elements in the range" ) {
        const vector<int> vec{5, 10, 100};

        const int initial_value = 1;
        const int expected = initial_value * 5 * 10 * 100;

        auto multiply = [](int x, int y) { return x * y; };
    
        const int product = accumulate(
                                  cbegin(vec)
                                , cend(vec)
                                , initial_value
                                , multiply
                            );    
                  
        REQUIRE( product == expected ); 
    } 

}

TEST_CASE( "adjacent_difference", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute dfference between next element and its previous element writing the result to the different range" ) {
        const vector<int>      vec{4, 9, 15, 22, 30};
              vector<int>   result;
        const vector<int> expected{4, 5,  6,  7,  8};

        adjacent_difference(cbegin(vec), cend(vec), back_inserter(result));    
                  
        REQUIRE( result == expected ); 
    } 

    SECTION( "compute absolute dfference between next element and its previous element writing the result to the different range" ) {
        const vector<int>      vec{4, -9, 15, -22, -30};
              vector<int>   result;
        const vector<int> expected{4,  5,  6,   7,   8};


        auto diff = [](int x, int y) { return abs(abs(x) - abs(y)); };

        adjacent_difference(cbegin(vec), cend(vec), back_inserter(result), diff);    
                  
        REQUIRE( result == expected ); 
    } 

}

TEST_CASE( "inner_product", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute sum(+) of products(*)" ) {
        const vector<int> vec1{1, 2, 3};
        const vector<int> vec2{4, 5, 6};
        
        const int initial_value = 10; 
        const int expected = initial_value + (1 * 4)  +  (2 * 5)  +  (3 * 6);

        const int result = inner_product(
                                 cbegin(vec1)
                               , cend(vec1) 
                               , cbegin(vec2) 
                               , initial_value
                           ); 
                  
        REQUIRE( result == expected ); 
    } 

    SECTION( "compute products(*) of sum(+)" ) {
        const vector<int> vec1{1, 2, 3};
        const vector<int> vec2{4, 5, 6};
        
        const int initial_value = 10; 
        const int expected = initial_value * (1 + 4)  *  (2 + 5)  *  (3 + 6);

        auto op1 = [](int x, int y) { return x * y; };
        auto op2 = [](int x, int y) { return x + y; };

        const int result = inner_product(
                                 cbegin(vec1)
                               , cend(vec1) 
                               , cbegin(vec2) 
                               , initial_value
                               , op1
                               , op2
                           ); 
                  
        REQUIRE( result == expected ); 
    }

}

TEST_CASE( "iota", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "fill the range with sequentially incremented values" ) {
              vector<int>      vec(5);
        const vector<int> expected{1, 2, 3, 4, 5};
        
        const int start_value = 1;
        
        iota(begin(vec), end(vec), start_value);
                  
        REQUIRE( vec == expected ); 
    } 

}

TEST_CASE( "partial_sum", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute partial sum of elements in the range and write results to another range" ) {
              vector<int>      vec{1, 2, 3,  4,  5};
              vector<int>   result;
        const vector<int> expected{1, 3, 6, 10, 15};
        
        partial_sum(cbegin(vec), cend(vec), back_inserter(result));
                  
        REQUIRE( result == expected ); 
    } 

    SECTION( "compute partial product(*) of elements in the range and write results to another range" ) {
              vector<int>      vec{1, 2, 3,  4,  5};
              vector<int>   result;
        const vector<int> expected{1, 2, 6, 24, 120};
        
        auto multiply = [](int x, int y) { return x * y; };
        
        partial_sum(cbegin(vec), cend(vec), back_inserter(result), multiply);
                  
        REQUIRE( result == expected ); 
    } 

}

TEST_CASE( "reduce(C++17)", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "out of order compute sum of all elements in the range plus the initial value" ) {
        const vector<int> vec{1, 2, 3};

        const int initial_value = 10; 
        const int expected = initial_value + 1 + 2 + 3;

        const int sum = reduce(cbegin(vec), cend(vec), initial_value);    
                  
        REQUIRE( sum == expected ); 
    } 

    SECTION( "out of order compute product of all elements in the range" ) {
        const vector<int> vec{5, 10, 100};

        const int initial_value = 1;
        const int expected = initial_value * 5 * 10 * 100;

        const int product = reduce(
                                  cbegin(vec)
                                , cend(vec)
                                , initial_value
                                , multiplies()
                            );    
                  
        REQUIRE( product == expected ); 
    } 
}

TEST_CASE( "exclusive_scan(C++17)", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "Computes an exclusive prefix sum" ) {
        const vector<int>       vec{1, 2, 3};
              vector<int>  expected{5, 6, 8};
              vector<int> generated{};

        const int initial_value = 5; 

        exclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
            , initial_value
        );
                  
        REQUIRE(  generated == expected ); 
    } 

    SECTION( "Computes an exclusive prefix product" ) {
        const vector<int>       vec{1, 2, 3};
              vector<int>  expected{5, 5, 10};
              vector<int> generated{};

        const int initial_value = 5; 

        exclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
            , initial_value
            , multiplies()
        );
                  
        REQUIRE(  generated == expected ); 
    }

}

TEST_CASE( "inclusive_scan(C++17)", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "Computes an inclusive prefix sum" ) {
        const vector<int>       vec{1, 2, 3};
              vector<int>  expected{1, 3, 6};
              vector<int> generated{};

        inclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
        );
                  
        REQUIRE(  generated == expected ); 
    } 

    SECTION( "Computes an inclusive prefix product" ) {
        const vector<int>       vec{1, 2, 3, 4};
              vector<int>  expected{1, 2, 6, 24};
              vector<int> generated{};

        inclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
            , multiplies()
        );
                  
        REQUIRE(  generated == expected ); 
    }

}

TEST_CASE( "transform_reduce(C++17)", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "out of order transform a range of elements and then apply the functor" ) {
        vector<string>  vec{"how", "many", "chars", "in", "the", "string"};

        auto transform = [](const string& str) { return str.size(); };
        auto reduce = [](size_t x, size_t y) { return x + y; };
        const size_t initial_value = 0;

        size_t number_of_chars = transform_reduce(
                             begin(vec)
                           , end(vec)
                           , initial_value
                           , reduce
                           , transform
                        );

        REQUIRE( number_of_chars == 23 );
    }

}

TEST_CASE( "transform_exclusive_scan(C++17)", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "transforms each element and computes an exclusive prefix sum" ) {
        const vector<int>       vec{0, 1, 2};
              vector<int>  expected{5, 6, 8};
              vector<int> generated{};

        const int initial_value = 5; 

        auto transform = [](int x) { return x+1; };

        transform_exclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
            , initial_value
            , plus()
            , transform
        );
                  
        REQUIRE(  generated == expected ); 
    } 

}

TEST_CASE( "transform_inclusive_scan(C++17)", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "transforms each element and computes an inclusive prefix sum" ) {
        const vector<int>       vec{0, 1, 2};
              vector<int>  expected{1, 3, 6};
              vector<int> generated{};


        auto transform = [](int x) { return x+1; };

        transform_inclusive_scan(
              begin(vec)
            , end(vec)
            , back_inserter(generated)
            , plus()
            , transform
        );
                  
        REQUIRE(  generated == expected ); 
    } 

}
