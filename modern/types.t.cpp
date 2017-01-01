#include <catch.hpp>
#include <type_traits>
#include <map>
#include <string>
#include <vector>

using namespace std;

TEST_CASE( "auto", "[std] [modern] [types]" ) {
    
    SECTION( "extreme readability for complex types" ) {
        map<string, map<int, vector<int>>> complex_container; 

        auto readable = begin(complex_container);

        map<string, map<int, vector<int>>>::iterator non_readable = begin(complex_container);

        REQUIRE( readable == non_readable );
    }

    SECTION( "deduced type based on initialization" ) {
        auto d = 12.34;
        static_assert( is_same<double, decltype(d)>::value, "expected double" );

        auto b = true;
        static_assert( is_same<bool, decltype(b)>::value, "expected bool" );

        auto i = 0;
        static_assert( is_same<int, decltype(i)>::value, "expected int" );

        auto& int_ref = i;
        static_assert( is_same<int&, decltype(int_ref)>::value, "expected int&" );

        const auto& const_int_ref = i;
        static_assert( is_same<const int&, decltype(const_int_ref)>::value, "expected const int&" );

        auto&& not_rvalue_ref = i;
        static_assert( is_same<int&, decltype(not_rvalue_ref)>::value, "expected int&" );

        auto&& rvalue_ref = 12345;
        static_assert( is_same<int&&, decltype(rvalue_ref)>::value, "expected int&&" );

        auto ptr = new int;
        static_assert( is_same<int*, decltype(ptr)>::value, "expected int*" );
        delete ptr;

        auto init_list = {1};
        static_assert( is_same<initializer_list<int>, decltype(init_list)>::value, "expected initializer_list<int>" );
    }

    SECTION( "deduced type based on function return" ) {
        auto lambda = [] () -> int { return 100; };
        auto value = lambda();
        static_assert( is_same<int, decltype(value)>::value, "expected int" );
    }

    SECTION( "deduced function return type" ) {
        class F {
        public:
            static auto add(int x, double y) {
                return x + y;
            }
        };

        auto value = F::add(12, 14.5);
        static_assert( is_same<double, decltype(value)>::value, "expected double" );
    }

    SECTION( "trailing return type" ) {
        class F {
        public:
            static auto add(int x, float y) -> double  {
                return x + y;
            }
        };

        auto value = F::add(12, 14.5);
        static_assert( is_same<double, decltype(value)>::value, "expected double" );
    }

}

TEST_CASE( "decltype", "[std] [modern] [types]" ) {

    SECTION( "declare variable based on the type of the expression" ) {
        int x = 12345;
        decltype(x) y;
        static_assert( is_same<int, decltype(y)>::value, "expected int" );

        decltype(12345) i;
        static_assert( is_same<int, decltype(i)>::value, "expected int" );

        decltype(12.34) d;
        static_assert( is_same<double, decltype(d)>::value, "expected double" );

        decltype(true) b;
        static_assert( is_same<bool, decltype(b)>::value, "expected bool" );
        
        int& int_ref1 = x;
        decltype(int_ref1) int_ref2 = x;
        static_assert( is_same<int&, decltype(int_ref2)>::value, "expected int&" );

        const int& const_int_ref1 = x;
        decltype(const_int_ref1) const_int_ref2 = x;
        static_assert( is_same<const int&, decltype(const_int_ref2)>::value, "expected const int&" );
        
        int&& rvalue_ref1 = 12345;
        decltype(rvalue_ref1) rvalue_ref2 = 54321;
        static_assert( is_same<int&&, decltype(rvalue_ref2)>::value, "expected int&&" );

        decltype( (x) ) another_way_int_ref = x;
        static_assert( is_same<int&, decltype(another_way_int_ref)>::value, "expected int&&" );
    }

    SECTION( "trailing return type" ) {
        class F {
        public:
            static auto add(int x, float y) -> decltype(x + y)  {
                return x + y;
            }
        };

        auto value = F::add(12, 14.5);
        static_assert( is_same<float, decltype(value)>::value, "expected float" );
    }

}

TEST_CASE( "decltype(auto)", "[std] [modern] [types]" ) {

    SECTION( "preserve const / volatile / reference" ) {
        class F {
        public:
            static int ret_int(int& i) { return i; }
            static int& ret_int_ref(int& i) { return i; }
            static const int& ret_const_int_ref(int& i) { return i; }
            static volatile int& ret_volatile_int_ref(int& i) { return i; }
        };

        int i = 0;

        decltype(auto) v = F::ret_int(i);
        static_assert( is_same<int, decltype(v)>::value, "expected int" );

        decltype(auto) int_ref = F::ret_int_ref(i);
        static_assert( is_same<int&, decltype(int_ref)>::value, "expected int&" );

        decltype(auto) const_int_ref = F::ret_const_int_ref(i);
        static_assert( is_same<const int&, decltype(const_int_ref)>::value, "expected const int&" );

        decltype(auto) volatile_int_ref = F::ret_volatile_int_ref(i);
        static_assert( is_same<volatile int&, decltype(volatile_int_ref)>::value, "expected volatile int&" );
    }

}
