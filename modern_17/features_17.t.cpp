#include <catch.hpp>
#include <random>
#include <unordered_map>

using namespace std;

TEST_CASE( "if initializer", "[std] [modern] [if/switch initializers] [C++17]" ) {
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

TEST_CASE( "switch initializer", "[std] [modern] [if/switch initializers] [C++17]" ) {
    SECTION( "switch" ) 
    {
        auto rand_1_2_3 = []() {
            random_device r;
            default_random_engine e(r());
            uniform_int_distribution<int> uniform_dist(1, 3);
            return uniform_dist(e);
        };   

        int mult = 2;
        switch(int i = rand_1_2_3(); i)
        {
            case 1:
                REQUIRE( i == 1 );
                mult = i;
                break;
            default:
                mult *= i;
                break;
        }
        REQUIRE( (mult == 4 || mult == 6 || mult == 1) );
    }
}

TEST_CASE( "lambda capture of *this", "[std] [modern] [lambda]" ) {
    class A {
    private:
        int m_x;

    public:
        A(int x): m_x(x) {}

        auto get_lambda_that_will_return_the_value_of_x() {
            auto lambda = [*this] { return m_x; };
            return lambda; 
        }

        int get_x() { return m_x; }

    };

    SECTION( "return lambda from member function that captures copy of A" ) {
        auto lambda = A{10}.get_lambda_that_will_return_the_value_of_x();
        REQUIRE( lambda() == 10 );
    }
}