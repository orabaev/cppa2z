#include <catch.hpp>
#include <random>
#include <unordered_map>
#include <type_traits>
#include <vector>
#include <map>

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

TEST_CASE( "lambda capture of *this", "[std] [modern] [lambda] [C++17]" ) {
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

TEST_CASE( "constexpr lambda", "[std] [modern] [lambda] [C++17]" ) {
    SECTION( "explicit constexpr lambda" ) {
        constexpr auto sqr = [] (int x) { return x * x; };
        static_assert( sqr(3) == 9 );
    }

    SECTION( "implicit constexpr lambda" ) {
        auto sqr = [] (int x) { return x * x; };
        static_assert( sqr(3) == 9 );
    }
}

TEST_CASE( "class template argument deduction", "[std] [modern] [temlates] [C++17]" ) {
    SECTION("vector")
    {   
        vector v1{1,2,3,4,5};
        vector<int> v2;
        static_assert(is_same_v<decltype(v1), decltype(v2)>);
    }

    SECTION("set")
    {   
        set s1{"str1"s, "str2"s};
        set<string> s2;
        static_assert(is_same_v<decltype(s1), decltype(s2)>);
    }

    SECTION("pair")
    {   
        pair p1(1,3);
        pair<int, int> p2;
        static_assert(is_same_v<decltype(p1), decltype(p2)>);
    }
}

template<class T> constexpr bool is_vector_f()
{
    using TYPE = typename decay<T>::type;
    using VECTOR = vector<typename TYPE::value_type, typename TYPE::allocator_type>;
    return is_same_v<TYPE, VECTOR>;
}