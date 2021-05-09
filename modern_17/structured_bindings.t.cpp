#include <catch.hpp>
#include <tuple>
#include <string>
#include <array>
#include <unordered_map>

using namespace std;

TEST_CASE( "data members", "[std] [modern] [structrued bundings] [C++17]" ) {
    SECTION( "pair bind all members" ) 
    {
        pair<string, int> person("Alice", 65);
        auto [name, age] = person; 

        REQUIRE( name == "Alice" );
        REQUIRE( age == 65 ); 
    }

    SECTION( "pair bind some members" ) 
    {
        pair<string, int> person("Alice", 65);
        auto [name, _] = person; 

        REQUIRE( name == "Alice" );
    }

    SECTION( "custom class" ) 
    {
        struct Person
        {
            string first_name;
            string last_name;
            int    age;
        };

        Person person{"Alice", "Wonder", 65};
        auto [first, last, age] = person; 

        REQUIRE( first == "Alice" );
        REQUIRE( last == "Wonder" );
        REQUIRE( age == 65 );
    }

    SECTION( "nested classes" ) 
    {
        struct Name
        {
            string first_name;
            string last_name;
        };

        struct Person
        {
            Name   name;
            int    age;
        };

        // :( not possible
        // auto [[first, last], age] = person; 

        Person person{{"Alice", "Wonder"}, 65};
        auto [name, age] = person; 
        auto [first, last] = name;

        REQUIRE( first == "Alice" );
        REQUIRE( last == "Wonder" );
        REQUIRE( age == 65 );
    }
}

TEST_CASE( "arrays", "[std] [modern] [structrued bundings] [C++17]" ) {
    SECTION( "C style array" ) 
    {
        int point_3D[] = {1,2,3};

        auto [x,y,z] = point_3D;

        REQUIRE( x == 1 );
        REQUIRE( y == 2 );
        REQUIRE( z == 3 );
    }

    SECTION( "C++ style array" ) 
    {
        array<int,3> point_3D{1,2,3};

        auto [x,y,z] = point_3D;

        REQUIRE( x == 1 );
        REQUIRE( y == 2 );
        REQUIRE( z == 3 );
    }
}

TEST_CASE( "tuple ", "[std] [modern] [structrued bundings] [C++17]" ) {
    SECTION( "tuple" ) 
    {
        tuple<string,string,int> person{"Alice","Wonder",65};

        auto [first, last, age] = person; 

        REQUIRE( first == "Alice" );
        REQUIRE( last == "Wonder" );
        REQUIRE( age == 65 );
    }
}

TEST_CASE( "range loop ", "[std] [modern] [structrued bundings] [C++17]" ) {
    SECTION( "[key,value]" ) 
    {
        unordered_map<string, int> dic;
        dic["S1"] = 2;
        dic["S2"] = 4;
        dic["S3"] = 8;

        for (const auto& [key, value] : dic)
        {
            REQUIRE( key[0] == 'S' );
            REQUIRE( value % 2 == 0 );
        }
    }

    SECTION( "key only" ) 
    {
        unordered_map<string, int> dic;
        dic["S1"] = 2;
        dic["S2"] = 4;
        dic["S3"] = 8;

        for (const auto& [key, _] : dic)
        {
            REQUIRE( key[0] == 'S' );
        }
    }

    SECTION( "value only" ) 
    {
        unordered_map<string, int> dic;
        dic["S1"] = 2;
        dic["S2"] = 4;
        dic["S3"] = 8;

        for (const auto& [_, value] : dic)
        {
            REQUIRE( value % 2 == 0 );
        }
    }
}

TEST_CASE( "tie", "[std] [modern] [structrued bundings] [C++17]" ) {
    SECTION( "reassign" ) 
    {
        pair<string, int> person("Alice", 65);
        auto [name, age] = person; 
        REQUIRE( name == "Alice" );
        REQUIRE( age == 65 ); 


        pair<string, int> different_person("Bob", 66);
        tie(name, age) = different_person; 

        REQUIRE( name == "Bob" );
        REQUIRE( age == 66 ); 
    }
}

