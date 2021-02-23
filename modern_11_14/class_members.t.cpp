#include <catch.hpp>
#include <type_traits>

using namespace std;

TEST_CASE( "delegating constructors", "[std] [modern] [class members]" ) {
    
    SECTION( "call constructor from withing another constructor" ) {
        struct three_members {
            int m_x, m_y, m_z;    

            three_members(int x, int y, int z)
            : m_x(x)
            , m_y(y)
            , m_z(z) 
            { }

            three_members(int x, int y)
            : three_members(x, y, 0)
            { }

            three_members(int x)
            : three_members(x, 0, 0)
            { }
        };

        three_members ctor1(1, 2, 3);

        REQUIRE( ctor1.m_x == 1);
        REQUIRE( ctor1.m_y == 2);
        REQUIRE( ctor1.m_z == 3);


        three_members ctor2(1, 2);

        REQUIRE( ctor2.m_x == 1);
        REQUIRE( ctor2.m_y == 2);
        REQUIRE( ctor2.m_z == 0);


        three_members ctor3(1);

        REQUIRE( ctor3.m_x == 1);
        REQUIRE( ctor3.m_y == 0);
        REQUIRE( ctor3.m_z == 0);
    }

}

TEST_CASE( "default functions", "[std] [modern] [class members]" ) {
    
    SECTION( "explicitly defined default functions" ) {
    
        struct A {
             int i;
             string s;

             A()                     = default;
             A(const A&)             = default;
             A(A&&)                  = default;
             A& operator=(const A&)  = default;
             A& operator=(A&&)       = default;
             ~A()                    = default;
        };

        static_assert( is_default_constructible<A>::value , "expected to be default constructible" );
        static_assert( is_copy_constructible<A>::value    , "expected to be copy constructible" );
        static_assert( is_move_constructible<A>::value    , "expected to be move constructible" );
        static_assert( is_copy_assignable<A>::value       , "expected to be copy assignable" );
        static_assert( is_move_assignable<A>::value       , "expected to be move assignable" );
        static_assert( is_constructible<A>::value         , "expected to be constructible" );

    }

    SECTION( "compilier degenerated default functions" ) {
    
        struct A {
             int i;
             string s;
        };

        static_assert( is_default_constructible<A>::value , "expected to be default constructible" );
        static_assert( is_copy_constructible<A>::value    , "expected to be copy constructible" );
        static_assert( is_move_constructible<A>::value    , "expected to be move constructible" );
        static_assert( is_copy_assignable<A>::value       , "expected to be copy assignable" );
        static_assert( is_move_assignable<A>::value       , "expected to be move assignable" );
        static_assert( is_constructible<A>::value         , "expected to be constructible" );

    }

}

TEST_CASE( "deleted functions", "[std] [modern] [class members]" ) {
    
    SECTION( "delete default constructor" ) {
        struct A {
             int i;
             string s;

             A() = delete;
        };

        static_assert( is_default_constructible<A>::value == 0 , "expected not to be default constructible" );
        static_assert( is_copy_constructible<A>::value         , "expected to be copy constructible" );
        static_assert( is_move_constructible<A>::value         , "expected to be move constructible" );
        static_assert( is_copy_assignable<A>::value            , "expected to be copy assignable" );
        static_assert( is_move_assignable<A>::value            , "expected to be move assignable" );
    }

    SECTION( "delete copy constructor" ) {
        struct A {
             int i;
             string s;

             A(const A&) = delete;
        };

        static_assert( is_default_constructible<A>::value == 0 , "expected not to be default constructible" );
        static_assert( is_copy_constructible<A>::value == 0    , "expected not to be copy constructible" );
        static_assert( is_move_constructible<A>::value == 0    , "expected not to be move constructible" );
        static_assert( is_copy_assignable<A>::value            , "expected to be copy assignable" );
        static_assert( is_move_assignable<A>::value            , "expected to be move assignable" );
    }

    SECTION( "delete move constructor" ) {
        struct A {
             int i;
             string s;

             A(const A&&) = delete;
        };

        static_assert( is_default_constructible<A>::value == 0 , "expected not to be default constructible" );
        static_assert( is_copy_constructible<A>::value == 0    , "expected not to be copy constructible" );
        static_assert( is_move_constructible<A>::value == 0    , "expected not to be move constructible" );
        static_assert( is_copy_assignable<A>::value == 0       , "expected not to be copy assignable" );
        static_assert( is_move_assignable<A>::value == 0       , "expected not to be move assignable" );
    }

    SECTION( "delete copy operator=" ) {
        struct A {
             int i;
             string s;

             A operator=(const A&) = delete;
        };

        static_assert( is_default_constructible<A>::value      , "expected to be default constructible" );
        static_assert( is_copy_constructible<A>::value         , "expected to be copy constructible" );
        static_assert( is_move_constructible<A>::value         , "expected to be move constructible" );
        static_assert( is_copy_assignable<A>::value == 0       , "expected not to be copy assignable" );
        static_assert( is_move_assignable<A>::value == 0       , "expected not to be move assignable" );
    }

    SECTION( "delete move operator=" ) {
        struct A {
             int i;
             string s;

             A operator=(A&&) = delete;
        };

        static_assert( is_default_constructible<A>::value      , "expected to be default constructible" );
        static_assert( is_copy_constructible<A>::value == 0    , "expected not to be copy constructible" );
        static_assert( is_move_constructible<A>::value == 0    , "expected not to be move constructible" );
        static_assert( is_copy_assignable<A>::value == 0       , "expected not to be copy assignable" );
        static_assert( is_move_assignable<A>::value == 0       , "expected not to be move assignable" );
    }

    SECTION( "delete desctructor" ) {
        struct A {
             int i;
             string s;

             ~A() = delete;
        };

        static_assert( is_default_constructible<A>::value == 0 , "expected not to be default constructible" );
        static_assert( is_copy_constructible<A>::value == 0    , "expected not to be copy constructible" );
        static_assert( is_move_constructible<A>::value == 0    , "expected not to be move constructible" );
        static_assert( is_copy_assignable<A>::value            , "expected to be copy assignable" );
        static_assert( is_move_assignable<A>::value            , "expected to be move assignable" );

        static_assert( is_constructible<A>::value == 0         , "expected not to be move constructible" );
    }

}

TEST_CASE( "explicit virtual overrides", "[std] [modern] [class members]" ) {
    
    SECTION( "overriding non virtual function is a compile error" ) {
        struct base {
            virtual ~base(){}
           
            virtual void func() {} 
             
        };

        struct derived :public base {
            virtual void func() override {} 

            // COMPILE ERROR 
            // virtual void was_not_defined_virtual_in_base_class() override {} 
        };
    }

}

TEST_CASE( "final specifier", "[std] [modern] [class members]" ) {
    
    SECTION( "overriding function marked final is compile error" ) {
        struct base {
            virtual void func() {} 
        };

        struct derived_a : public base {
            virtual void func() final {} 
        };

        struct derived_b : public derived_a {
            // COMPILE ERROR 
            // declaration of 'func' overrides a 'final' function 
            // virtual void func() {} 
        };
    }

    SECTION( "cannot inherit from base class marked final" ) {
        struct base final {

        };

        // COMPILE ERROR 
        // base 'base' is marked 'final' 

        //struct derived : base {

        //};
    }

    SECTION( "only virtual member function can be marked final" ) {
        struct base {
        };

        struct derived  {
            // COMPILE ERROR 
            // only virtual member functions can be marked 'final' 
            // void func() final {} 
        };
    }

}
