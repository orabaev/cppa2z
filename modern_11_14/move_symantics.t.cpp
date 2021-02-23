#include <catch.hpp>
#include <type_traits>
#include <utility>
#include <string>
#include <vector>

using namespace std;

TEST_CASE( "rvalue references", "[std] [modern] [move symantics]" ) {
    
    SECTION( "named rvalue reference is an lvalue" ) {
        int&& named_rvalue_ref1 = 0;
        named_rvalue_ref1 = 1;

        static_assert( is_same<int&&, decltype(named_rvalue_ref1)>::value, "expected int&&" );
        static_assert( is_rvalue_reference<decltype(named_rvalue_ref1)>::value, "expected rvalue reference" );


        auto returns_value = []() -> int { return 0; };
        int&& named_rvalue_ref2 = returns_value();
        named_rvalue_ref2 = 1; 

        static_assert( is_same<int&&, decltype(named_rvalue_ref2)>::value, "expected int&&" );
        static_assert( is_rvalue_reference<decltype(named_rvalue_ref2)>::value, "expected rvalue reference" );
    }

    SECTION( "unnamed rvalue reference is an rvalue" ) {
        int x = 0;

        static_assert( is_rvalue_reference<decltype(static_cast<int&&>(x))>::value, "expected unnamed rvalue ref" );
        // COMPILE ERROR static_cast<int&&>(x) = 1;

        move(x); // unnamed
        // COMPILE ERROR move(x) = 2;
    }

    SECTION( "only unnamed rvalue references can be passed as parameters to functions" ) {
        auto function_that_takes_rvalue_ref = [] (int&& x) { };

        int lvalue = 0;
        function_that_takes_rvalue_ref( static_cast<int&&>(lvalue) );
        function_that_takes_rvalue_ref( move(lvalue) );
        // COMPILE ERROR function_that_takes_rvalue_ref( lvalue );

        int& lvalue_ref = lvalue;
        function_that_takes_rvalue_ref( static_cast<int&&>(lvalue_ref) );
        function_that_takes_rvalue_ref( move(lvalue_ref) );
        // COMPILE ERROR function_that_takes_rvalue_ref( lvalue_ref );

        int&& named_rvalue_ref = 0;
        function_that_takes_rvalue_ref( static_cast<int&&>(named_rvalue_ref) );
        function_that_takes_rvalue_ref( move(named_rvalue_ref) );
        // COMPILE ERROR function_that_takes_rvalue_ref( named_rvalue_ref );
    }

}

TEST_CASE( "std.move", "[std] [modern] [move symantics]" ) {

    SECTION( "move always returns unnamed rvalue reference" ) {
        int lvalue = 0;
        static_assert( is_same<decltype(move(lvalue)), int&&>::value, "expected int&&" );

        int& lvalue_ref = lvalue;
        static_assert( is_same<decltype(move(lvalue_ref )), int&&>::value, "expected int&&" );

        int&& rvalue_ref = 0;
        static_assert( is_same<decltype(move(rvalue_ref)), int&&>::value, "expected int&&" );

        static_assert( is_same<decltype(move(move(rvalue_ref))), int&&>::value, "expected int&&" );
    }

    SECTION( "move vector of strings" ) {
        vector<string>           from{"Hello", "C++", "move", "symantics"};
        vector<string>             to;
        const vector<string> expected{"Hello", "C++", "move", "symantics"};
        
        to = move(from); 

        REQUIRE( to == expected );
    }

}

class forward_example {
private:
    static string func(int&& value) {
        return string{"int&&"};
    }

    static string func(int& value) {
        return string{"int&"};
    }

    static string func(const int& value) {
        return string{"const int&"};
    }

public:
    template<class T>
    static string perfect_forwarding_wrapper(T&& value)
    {
        return func(forward<T>(value));
    }

};

TEST_CASE( "std.forward", "[std] [modern] [move symantics]" ) {

    SECTION( "move always returns unnamed rvalue reference" ) {
        int lvalue = 0;

        REQUIRE( forward_example::perfect_forwarding_wrapper(move(lvalue)) == "int&&" );

        REQUIRE( forward_example::perfect_forwarding_wrapper(lvalue) == "int&" );

        const int& const_ref = lvalue;
        REQUIRE( forward_example::perfect_forwarding_wrapper(const_ref) == "const int&" );
    }

}

TEST_CASE( "special member functions", "[std] [modern] [move symantics]" ) {

    class special_member_functions {
    private:
        string m_str;   

        string m_which_function_was_called;

    public:
        special_member_functions(const string& str) 
        : m_str(str) 
        {
            
        }

        // copy constructor
        special_member_functions(const special_member_functions& obj)
        : m_str( obj.m_str ) 
        {
            m_which_function_was_called = "copy constructor";
        }
        
        // SPECIAL function move constructor
        special_member_functions(special_member_functions&& obj)
        : m_str( move(obj.m_str) ) 
        {
            m_which_function_was_called = "move constructor";
        }

        // copy assignment operator
        special_member_functions& operator=(const special_member_functions& obj) {
            string temp_exception_safe = obj.m_str;    
            m_str = move(temp_exception_safe); 

            m_which_function_was_called = "copy assignment operator";
            return *this;
        }

        // SPECIAL function move assignment operator
        special_member_functions& operator=(special_member_functions&& obj) {
            m_str = move(obj.m_str);

            m_which_function_was_called = "move assignment operator";
            return *this;
        }

        const string& which_function_was_called() {
            return m_which_function_was_called;
        }

        const string& str() {
            return m_str;
        }
         
    };

    SECTION( "copy constructor" ) {
        special_member_functions from("special");
        
        special_member_functions copy_to(from);
        REQUIRE(  copy_to.which_function_was_called() == "copy constructor" );
        REQUIRE(  copy_to.str() == "special" );
    }

    SECTION( "move constructor" ) {
        special_member_functions from("class");
        
        special_member_functions move_to( move(from) );
        REQUIRE( move_to.which_function_was_called() == "move constructor" );
        REQUIRE( move_to.str() == "class" );
    }

    SECTION( "copy assignment operator" ) {
        special_member_functions from("memeber");
        
        special_member_functions copy_assign_to("");
        copy_assign_to = from; 

        REQUIRE( copy_assign_to.which_function_was_called() == "copy assignment operator" );
        REQUIRE( copy_assign_to.str() == "memeber" );
    }

    SECTION( "move assignment operator" ) {
        special_member_functions from("functions");
        
        special_member_functions move_assign_to("");
        move_assign_to = move(from); 

        REQUIRE( move_assign_to.which_function_was_called() == "move assignment operator" );
        REQUIRE( move_assign_to.str() == "functions" );
    }

}
