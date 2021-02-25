#include <catch.hpp>
#include <type_traits>
#include <any>
#include <optional>
#include <variant>
#include <string>
#include <string_view>

using namespace std;

TEST_CASE( "any", "[std] [modern] [any] [C++17]" ) {
    SECTION( "with no value" ) {
        any a;
        REQUIRE_FALSE( a.has_value());
    }
    
    SECTION( "with value" ) {
        any a = 11;
        REQUIRE( a.has_value());
        REQUIRE( any_cast<int>(a) == 11 );

        a = string("Hello");
        REQUIRE( any_cast<string>(a) == "Hello" );
    }

    SECTION( "bad_any_cast" ) {
        any a = 11;
        REQUIRE_THROWS_AS( any_cast<double>(a), bad_any_cast );
        REQUIRE_THROWS_AS( any_cast<string>(a), bad_any_cast );
    }

    SECTION( "reset" ) {
        any a = 11;
        a.reset();
        REQUIRE_FALSE( a.has_value() );
    }

    SECTION( "type" ) {
        any a = 11;
        REQUIRE( a.type() == typeid(int) );
        a = string("Hello");
        REQUIRE( a.type() == typeid(string) );
    }
}

TEST_CASE( "optional", "[std] [modern] [optional] [C++17]" ) {
    SECTION( "with no value" ) {
        optional<string> opt;
        REQUIRE( opt == nullopt);
        REQUIRE_FALSE( opt );
        REQUIRE_FALSE( opt.has_value());
        REQUIRE( opt.value_or("default value") == "default value");
        REQUIRE_THROWS_AS( opt.value(), bad_optional_access);
    }

    SECTION( "with value" ) {
        optional<string> opt("Hello");
        REQUIRE( opt != nullopt);
        REQUIRE( opt.value() == "Hello");
        REQUIRE( opt.value_or("default value") == "Hello");
        REQUIRE( *opt == "Hello");
        REQUIRE( opt->size() == 5);
    }

    SECTION( "emplace" ) {
        optional<string> opt;
        opt.emplace("Hello");
        REQUIRE( *opt == "Hello");
    }

    SECTION( "reset" ) {
        optional<string> opt("Hello");
        REQUIRE( opt );
        opt.reset();
        REQUIRE_FALSE( opt );
    }

    SECTION( "move" ) {
        optional<string> opt1("Allocate very very very very very very long string");
        optional<string> opt2 = move(*opt1);
        REQUIRE( *opt2 == "Allocate very very very very very very long string" );
        REQUIRE( opt1 != opt2 );
    }

    SECTION( "assignment" ) {
        optional<string> opt1("Allocate very very very very very very long string");
        optional<string> opt2 = opt1;
        REQUIRE( opt1 == opt2 );

        opt1 = "Another string";
        REQUIRE( *opt1 == "Another string" );
    }

    SECTION( "make_optional" ) {
        auto opt = make_optional(123);
        REQUIRE( *opt == 123 );
    }
}

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
        REQUIRE( get<0>(var)   == 11 );
        REQUIRE( get<int>(var) == 11 );

        var = "Hello";
        REQUIRE( get<1>(var)      == "Hello" );
        REQUIRE( get<string>(var) == "Hello" );

        var = 123.456;
        REQUIRE( get<2>(var)      == 123.456 );
        REQUIRE( get<double>(var) == 123.456 );

        REQUIRE_THROWS_AS( get<0>(var), bad_variant_access );
    }

    SECTION( "get_if" ) {
        variant<int, string, double> var; 

        var = 11;
        REQUIRE( *get_if<int>(&var)   == 11 );
        REQUIRE( get_if<string>(&var) == nullptr );
        REQUIRE( get_if<double>(&var) == nullptr );

        var = "Hello";
        REQUIRE( get_if<int>(&var)     == nullptr );
        REQUIRE( *get_if<string>(&var) == "Hello" );
        REQUIRE( get_if<double>(&var)  == nullptr );

        var = 123.456;
        REQUIRE( get_if<int>(&var)     == nullptr );
        REQUIRE( get_if<string>(&var)  == nullptr );
        REQUIRE( *get_if<double>(&var) == 123.456 );
    }

    SECTION( "visit" ) {
        vector<variant<int, string, double>> vec;
        vec.emplace_back("Hello");
        vec.emplace_back(11);
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

TEST_CASE( "tuple", "[std] [modern] [tuple] [C++17]" ) {
    SECTION( "default ctor" ) {
        tuple<int, string, double> tpl;
        REQUIRE( get<int>(tpl) == 0 );
        REQUIRE( get<0>(tpl)   == 0 );

        REQUIRE( get<string>(tpl) == "" );
        REQUIRE( get<1>(tpl)      == "" );

        REQUIRE( get<double>(tpl) == 0.0 );
        REQUIRE( get<2>(tpl)      == 0.0 );
    }

    SECTION( "seting and geting the value" ) {
        tuple<int, string> tpl;
        get<int>(tpl) = 123;
        REQUIRE( get<0>(tpl) == 123 );

        get<1>(tpl) = "Hello";
        REQUIRE( get<string>(tpl) == "Hello" );
    }
    
    SECTION( "make_tuple" ) {
        auto tpl = make_tuple(123, string("Hello"));
        REQUIRE( get<0>(tpl) == 123     );
        REQUIRE( get<1>(tpl) == "Hello" );
    }

    SECTION( "tuple_cat" ) {
        auto tpl1 = make_tuple(123, string("Hello"));
        auto tpl2 = make_tuple(12.34, 321);
        auto tpl3 = tuple_cat(tpl1, tpl2);
        static_assert( tuple_size<decltype(tpl3)>::value == 4 );
        REQUIRE( get<0>(tpl3) == 123     );
        REQUIRE( get<1>(tpl3) == "Hello" );
        REQUIRE( get<2>(tpl3) == 12.34   );
        REQUIRE( get<3>(tpl3) == 321     );

        int i = 789;
        auto tpl4 = tuple_cat(tpl1, tie(i));
        REQUIRE( get<0>(tpl4) == 123     );
        REQUIRE( get<1>(tpl4) == "Hello" );
        REQUIRE( get<2>(tpl4) == 789     );
    }
}

TEST_CASE( "string_view", "[std] [modern] [string_view] [C++17]" ) {
    SECTION( "initialize from string" ) {
        string str{"Hello C++"};
        string_view sv(str);
        REQUIRE( sv == str );

        bool same_pointer = &str[0] == sv.data();
        REQUIRE( same_pointer );
    }

    SECTION( "initialize from char[]" ) {
        char str[] = "Hello C++";
        string_view sv(str);
        REQUIRE( sv == str );

        bool same_pointer = str == sv.data();
        REQUIRE( same_pointer );
    }

    SECTION( "operator sv" ) {
        string_view sv_proper_way_to_init_from_string_literal = "Hello C++"sv;
        REQUIRE( sv_proper_way_to_init_from_string_literal == "Hello C++" );
    }

    SECTION( "basic string operations" ) {
        string str{"Hello"};
        string_view sv(str);

        REQUIRE( *sv.begin()      == 'H' );
        REQUIRE( *prev(sv.end())  == 'o' );
        REQUIRE( *sv.rbegin()     == 'o' );
        REQUIRE( *prev(sv.rend()) == 'H' );

        REQUIRE( sv[0]      == 'H' );
        REQUIRE( sv.at(0)   == 'H' );
        REQUIRE( sv.front() == 'H' );
        REQUIRE( sv.back()  == 'o' );
        REQUIRE_THROWS_AS( sv.at(1000), out_of_range );

        REQUIRE( sv.size() == str.size() );
        REQUIRE( sv.size() == sv.length() );
        REQUIRE_FALSE( sv.empty() );
    }

    SECTION( "substr" ) {
        string str{"Hello C++"};
        string_view sv1(str);

        string_view sv2 = sv1.substr(0, 5);
        REQUIRE( sv2 == "Hello" );
        bool same_pointer  = sv1.data() == sv2.data();
             same_pointer &= sv2.data() == &str[0];
        REQUIRE( same_pointer );

        sv2 = sv1.substr(6);
        REQUIRE( sv2 == "C++" );
             same_pointer  = &sv1[6] == sv2.data();
             same_pointer &= sv2.data() == &str[6];
        REQUIRE( same_pointer );

    }

    SECTION( "remove_prefix" ) {
        string str{"...Hello"};
        string_view sv(str);

        REQUIRE( sv == "...Hello" );
        sv.remove_prefix(3);
        REQUIRE( sv == "Hello" );

        bool same_pointer = &str[3] == sv.data();
        REQUIRE( same_pointer );
    }

    SECTION( "remove_suffix" ) {
        string str{"Hello...."};
        string_view sv(str);

        REQUIRE( sv == "Hello...." );
        sv.remove_suffix(4);
        REQUIRE( sv == "Hello" );

        bool same_pointer = &str[0] == sv.data();
        REQUIRE( same_pointer );
    }

    SECTION( "swap" ) {
        string str1{"Hello"};
        string_view sv1(str1);

        string str2{"World"};
        string_view sv2(str2);

        swap(sv1, sv2);
        REQUIRE( sv1 == "World" );
        REQUIRE( sv2 == "Hello" );

        REQUIRE( str1 == "Hello" );
        REQUIRE( str2 == "World" );
    }

    SECTION( "swap" ) {
        string str1{"ABCDE"};
        string_view sv1(str1);

        char dest[5];
        sv1.copy(dest, 3, 1);
        REQUIRE( dest == string{"BCD"} );
    }

    SECTION( "find" ) {
        string str1{"ABCDE"};
        string_view sv1(str1);

        REQUIRE( sv1.find('C') == 2 );
        REQUIRE( sv1.find('C', 3) == string_view::npos );
        REQUIRE( sv1.find("DE") == 3 );

        int pos = 0;
        int count = 2;
        REQUIRE( sv1.find("DE__BLA_BLA", pos, count) == 3 );
    }

    SECTION( "starts_with" ) {
        // TODO_SWITCH_TO_CPP_20;
    }

    SECTION( "ends_with" ) {
        // TODO_SWITCH_TO_CPP_20;
    }

    SECTION( "contains" ) {
        // TODO_SWITCH_TO_CPP_20;
    }
}
