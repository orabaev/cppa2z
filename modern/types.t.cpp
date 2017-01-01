#include <catch.hpp>
#include <type_traits>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool runtime_is_const_ref(int& r) { return false; }
bool runtime_is_const_ref(const int& r) { return true; }

TEST_CASE( "auto", "[std] [modern] [types]" ) {
    
    SECTION( "extreme readability for complex types" ) {
        map<string, map<int, vector<int>>> complex_container; 

        auto readable = begin(complex_container);

        map<string, map<int, vector<int>>>::iterator non_readable = begin(complex_container);

        REQUIRE( readable == non_readable );
    }

    SECTION( "deduced type based on initialization" ) {
        auto d = 12.34;
        REQUIRE( typeid(d) == typeid(double) );

        auto b = true;
        REQUIRE( typeid(b) == typeid(bool) );

        auto i = 0;
        REQUIRE( typeid(i) == typeid(int) );

        auto& int_ref = i;
        REQUIRE( typeid(int_ref) == typeid(int) );
        REQUIRE( is_reference<decltype(int_ref)>::value );

        const auto& int_const_ref = i;
        REQUIRE( typeid(int_const_ref) == typeid(int) );
        REQUIRE( is_reference<decltype(int_const_ref)>::value );
        REQUIRE( runtime_is_const_ref(int_const_ref) );

        auto&& not_rvalue_ref = i;
        REQUIRE( typeid(not_rvalue_ref) == typeid(int) );
        REQUIRE( is_reference<decltype(not_rvalue_ref)>::value );
        REQUIRE_FALSE( is_rvalue_reference<decltype(not_rvalue_ref)>::value );

        auto&& rvalue_ref = 12345;
        REQUIRE( typeid(rvalue_ref) == typeid(int) );
        REQUIRE( is_rvalue_reference<decltype(rvalue_ref)>::value );

        auto ptr = new int;
        REQUIRE( typeid(ptr) == typeid(int*) );
        delete ptr;

        auto init_list = {1};
        REQUIRE( typeid(init_list) == typeid(initializer_list<int>) );
    }

    SECTION( "deduced type based on function return" ) {
        auto lambda = [] () -> int { return 100; };

        auto value = lambda();
        REQUIRE( typeid(value) == typeid(int) );
    }

    SECTION( "deduced function return type" ) {
        class F {
        public:
            static auto add(int x, double y) {
                return x + y;
            }
        };

        auto d = F::add(12, 14.5);
        REQUIRE( typeid(d) == typeid(double) );
    }

    SECTION( "trailing return type" ) {
        class F {
        public:
            static auto add(int x, float y) -> double  {
                return x + y;
            }
        };

        auto d = F::add(12, 14.5);
        REQUIRE( typeid(d) == typeid(double) );
    }

}
