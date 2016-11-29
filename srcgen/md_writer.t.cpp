#include <catch.hpp>
#include <md_writer.h>
#include <sstream>
#include <string>

using namespace std;

namespace srcgen {

TEST_CASE( "md_writer.ctor" ) {
    ostringstream out;
    md_writer writer(out);
}

TEST_CASE( "md_writer.heading1" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("heading1") {
        const string expected{"#Heading1\n"};

        writer.heading1("Heading1");

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"#Heading1\n#Other\n"};

        writer.heading1("Heading1")
              .heading1("Other");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.heading2" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("heading2") {
        const string expected{"##Heading2\n"};

        writer.heading2("Heading2");

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"##Heading2\n#Other\n"};

        writer.heading2("Heading2")
              .heading1("Other");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.heading3" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("heading3") {
        const string expected{"###Heading3\n"};

        writer.heading3("Heading3");

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"###Heading3\n#Other\n"};

        writer.heading3("Heading3")
              .heading1("Other");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.write" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("write") {
        const string expected{"value "};

        writer.write("value");

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"Hello World "};

        writer.write("Hello")
              .write("World");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.bold" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("bold") {
        const string expected{"**bold** "};

        writer.bold("bold");

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"**Hello** **World** "};

        writer.bold("Hello")
              .bold("World");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.newline" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("newline") {
        const string expected{"  \n"};

        writer.newline();

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"Hello   \nWorld "};

        writer.write("Hello")
              .newline()
              .write("World");

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.html_space" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("space") {
        const string expected{"&nbsp;"};

        writer.html_space();

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"&nbsp;&nbsp;"};

        writer.html_space().html_space();

        REQUIRE( expected == out.str() );
    }
}

TEST_CASE( "md_writer.link_to_repo_file" ) {
    ostringstream out;
    md_writer writer(out);

    SECTION("link_to_repo_file") {
        const string expected{"[link_name](https://github.com/orabaev/cppa2z/blob/master/algorithms/heap.t.cpp#L15) "};
        
        writer.link_to_repo_file(
              "link_name"
            , "https://github.com/orabaev/cppa2z/blob/master/algorithms/heap.t.cpp"
            , 15
        );

        REQUIRE( expected == out.str() );
    }

    SECTION("chain") {
        const string expected{"[link_name](https://github.com/orabaev/cppa2z/blob/master/algorithms/heap.t.cpp#L15) hello "};
        
        writer.link_to_repo_file(
                  "link_name"
                , "https://github.com/orabaev/cppa2z/blob/master/algorithms/heap.t.cpp"
                , 15)
              .write("hello");

        REQUIRE( expected == out.str() );
    }
}

} // namespace srcgen
