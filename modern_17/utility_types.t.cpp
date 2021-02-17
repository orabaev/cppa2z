#include <catch.hpp>
#include <type_traits>
#include <any>
#include <optional>
#include <variant>
#include <string>

using namespace std;

static int static_i = 0;

TEST_CASE( "variant", "[std] [modern] [variant] [C++17]" ) {
    SECTION( "index" ) {
        variant<int, string, double> var; 
        REQUIRE( var.index() == 0 );

        var = 11;
        REQUIRE( var.index() == 0 );

        var = "Hello";
        REQUIRE( var.index() == 1 );

        var = 123.456;
        REQUIRE( var.index() == 2 );

        var = {};
        REQUIRE( var.index() == 0 );
    }

    SECTION( "emplace" ) {
        variant<int, string, double> var; 

        var.emplace<int>(11);
        REQUIRE( var.index() == 0 );
        var.emplace<0>(11);
        REQUIRE( var.index() == 0 );

        var.emplace<string>("Hello");
        REQUIRE( var.index() == 1 );
        var.emplace<1>("Hello");
        REQUIRE( var.index() == 1 );

        var.emplace<double>(123.456);
        REQUIRE( var.index() == 2 );
        var.emplace<2>(123.456);
        REQUIRE( var.index() == 2 );
    }

    SECTION( "get" ) {
        variant<int, string, double> var; 

        var = 11;
        REQUIRE( get<0>(var) == 11 );
        REQUIRE( get<int>(var) == 11 );

        var = "Hello";
        REQUIRE( get<1>(var) == "Hello" );
        REQUIRE( get<string>(var) == "Hello" );

        var = 123.456;
        REQUIRE( get<2>(var) == 123.456 );
        REQUIRE( get<double>(var) == 123.456 );

        REQUIRE_THROWS_AS( get<0>(var), bad_variant_access );
    }

    SECTION( "get_if" ) {
        variant<int, string, double> var; 

        var = 11;
        REQUIRE( *get_if<int>(&var) == 11 );
        REQUIRE( get_if<string>(&var) == nullptr );
        REQUIRE( get_if<double>(&var) == nullptr );

        var = "Hello";
        REQUIRE( get_if<int>(&var) == nullptr );
        REQUIRE( *get_if<string>(&var) == "Hello" );
        REQUIRE( get_if<double>(&var) == nullptr );

        var = 123.456;
        REQUIRE( get_if<int>(&var) == nullptr );
        REQUIRE( get_if<string>(&var) == nullptr );
        REQUIRE( *get_if<double>(&var) == 123.456 );
    }

    SECTION( "visit" ) {
        vector<variant<int, string, double>> vec;
        vec.emplace_back(11);
        vec.emplace_back("Hello");
        vec.emplace_back(123.456);

        for (auto& var : vec)
        {
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>)
                    REQUIRE( arg == 11 );
                else if constexpr (std::is_same_v<T, string>)
                    REQUIRE( arg == "Hello" );
                else if constexpr (std::is_same_v<T, double>)
                    REQUIRE( arg == 123.456 );
                else
                    REQUIRE( false );
                    
            }, var);
        }
    }


    SECTION( "holds_alternative" ) {
        variant<int, string, double> var; 

        var = 11;
        REQUIRE( holds_alternative<int>(var) );
        REQUIRE_FALSE( holds_alternative<string>(var) );
        REQUIRE_FALSE( holds_alternative<double>(var) );

        var = "Hello";
        REQUIRE_FALSE( holds_alternative<int>(var) );
        REQUIRE( holds_alternative<string>(var) );
        REQUIRE_FALSE( holds_alternative<double>(var) );

        var = 123.456;
        REQUIRE_FALSE( holds_alternative<int>(var) );
        REQUIRE_FALSE( holds_alternative<string>(var) );
        REQUIRE( holds_alternative<double>(var) );
    }
}

