#include <catch.hpp>
#include <functional>
#include <vector>
#include <list>

using namespace std;

static int static_i = 0;

TEST_CASE( "[]", "[std] [modern] [lambda]" ) {
    
    SECTION( "default, capture nothing, minimal lambda called directly" ) {
        [] { static_i = 1; } ();

        REQUIRE( static_i == 1);
    }

    SECTION( "lambda called through assigned variable" ) {
        auto func = [] { static_i = 2; };

        func();

        REQUIRE( static_i == 2 );
    }

}

TEST_CASE( "(int x)", "[std] [modern] [lambda]" ) {

    SECTION( "passing parameters" ) {
        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( is_even(10) );
        REQUIRE_FALSE( is_even(11) );
    }

}

TEST_CASE( "[=]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variables by value" ) {
        const int x = 4;
        const int y = 3;

        auto add_x_y = [=] { return x + y; };

        const int ret = add_x_y();

        REQUIRE( ret == 7 );
    }

}

TEST_CASE( "lambda.mutable", "[std] [modern] [lambda]" ) {

    SECTION( "modified captured by value local variables" ) {
        int x = 0;

        auto set_x = [=] () mutable { x = 10; return x; };

        const int ret = set_x();

        REQUIRE( x   == 0);
        REQUIRE( ret == 10);
    }

}

TEST_CASE( "[&]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variables by reference" ) {
        int x = 3;
        int y = 4;

        auto reset = [&] { x = y = 0; };

        reset();

        REQUIRE( x == 0 );
        REQUIRE( y == 0 );
    }

}

TEST_CASE( "[&x, y]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variable x by reference and y by value" ) {
        int x = 0;
        int y = 7;

        auto x_assign_y = [&x, y] { x = y; };

        x_assign_y();

        REQUIRE( x == 7 );
    }

}

TEST_CASE( "-> type", "[std] [modern] [lambda]" ) {

    SECTION( "explicitly return a particular type from lambda" ) {
        auto sqr = [] (int x) -> double { return x * x; };

        const auto value = sqr(4);

        REQUIRE( value == 16.0 );
    }

}

TEST_CASE( "[=, &x]", "[std] [modern] [lambda]" ) {

    SECTION( "capture x by reference the rest by value" ) {
        int x = 0;
        int y = 1;
        int z = 2;

        auto x_assign_y_plus_z = [=, &x] { x = y + z; };

        x_assign_y_plus_z();

        REQUIRE( x == 3 );
    }

}

TEST_CASE( "[&, x]", "[std] [modern] [lambda]" ) {

    SECTION( "capture x by value the rest by reference" ) {
        int x = 2;
        int y = 0;
        int z = 0;

        auto change_y_z = [&, x] { y = x * x; z = x * x * x; };

        change_y_z();

        REQUIRE( y == 4 );
        REQUIRE( z == 8 );
    }

}

TEST_CASE( "capture this pointer.[this]", "[std] [modern] [lambda]" ) {

    class A {
    private:
        int m_x;

    public:
        A(int x): m_x(x) {}

        void reset_x_using_lambda() {
            auto lambda = [this] { m_x = 0; };

            lambda();
        }

        int get_x() { return m_x; }

    };

    SECTION( "use lambda from member function, the lambda has write access to the object state" ) {
        A a{10};
        REQUIRE( a.get_x() == 10 );

        a.reset_x_using_lambda();
        REQUIRE( a.get_x() == 0);
    }

}

TEST_CASE( "generic lambda.(auto x)", "[std] [modern] [lambda] [C++14]" ) {

     SECTION( "generic lambda expression" ) {
        
        auto replace_in_collection = [](auto& collection, const auto& from, const auto& to) {
                                         replace(begin(collection), end(collection), from, to); 
                                     };  
         
              vector<int>          vec{1, 2, 3, 1, 4, 1, 1};
        const vector<int> expected_vec{0, 2, 3, 0, 4, 0, 0};
        
        replace_in_collection(vec, 1, 0);
        REQUIRE( vec == expected_vec );


              list<int>          lst{1, 2, 3, 1, 4, 1, 1};
        const list<int> expected_lst{0, 2, 3, 0, 4, 0, 0};
        
        replace_in_collection(lst, 1, 0);
        REQUIRE( lst == expected_lst );

    }

}

TEST_CASE( "lambda capture initializer.(x = value)", "[std] [modern] [lambda] [C++14]" ) {

    SECTION( "increment by" ) {
        const int start_value  = 1;
        const int increment_by_value = 3;
           
        auto increment_by = [x = start_value] () mutable {
            // NOTE THAT increment_by_value is implicitly captured by lambda
            x += increment_by_value;                  
            return x; 
        };
 
        REQUIRE( increment_by() == 4 );
        REQUIRE( increment_by() == 7 );
        REQUIRE( increment_by() == 10 );
    }

    SECTION( "vector state in lambda" ) {
        vector<int> initial_values{1, 2};
           
        auto push_value_and_return = [vec = initial_values] (int x) mutable -> vector<int>& {
            vec.push_back(x);
            return vec; 
        };
 
        vector<int>& vec_ref = push_value_and_return(3);
        REQUIRE( vec_ref[0] == 1);
        REQUIRE( vec_ref[1] == 2);
        REQUIRE( vec_ref[2] == 3);

        REQUIRE( push_value_and_return(10)[3] == 10 );
        REQUIRE( push_value_and_return(7)[4] == 7 );

        REQUIRE( vec_ref[0] == 1);
        REQUIRE( vec_ref[1] == 2);
        REQUIRE( vec_ref[2] == 3);
        REQUIRE( vec_ref[3] == 10);
        REQUIRE( vec_ref[4] == 7);
    }

}

TEST_CASE( "callback", "[std] [modern] [lambda]" ) {

    SECTION( "function with lambda" ) {
        function<int (int,int)> operation;

        auto multiply = [] (int x, int y) -> int {
            return x * y;
        };

        operation = multiply;
        REQUIRE( operation(2,3) == 6 );
    }

    SECTION( "class with callback" ) {
        class class_with_callback {
        private:
            function<int (int) > m_callback;             

        public:
            int execute(int x) { 
                if (m_callback) return m_callback(x); 
                return 0;
            }

            void set_callback(decltype(m_callback) callback) {
                m_callback = callback;
            }
            
        };

        class_with_callback obj;

        auto x_times_x = [](int x) { return x * x; };
        obj.set_callback(x_times_x);

        REQUIRE( obj.execute(2) == 4 );

        auto x_times_x_times_x = [](int x) { return x * x * x; };
        obj.set_callback(x_times_x_times_x);

        REQUIRE( obj.execute(3) == 27 );
    }

}
