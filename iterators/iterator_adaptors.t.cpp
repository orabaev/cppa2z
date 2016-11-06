#include <catch.hpp>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include <list>
#include <deque>

using namespace std;

TEST_CASE( "inserter", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "insert values into the set using insert_iterator" ) {
        const vector<int>     from{3, 4, 2, 5, 1};
              set<int>          to;
        const set<int>    expected{1, 2, 3, 4, 5};

        auto output_it = inserter(to, end(to));

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    } 

    SECTION( "insert values into the list using insert_iterator" ) {
        const vector<int>     from{1, 2, 3, 4, 5};
              list<int>         to;
        const list<int>   expected{1, 2, 3, 4, 5};

        auto output_it = inserter(to, end(to));

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }

    SECTION( "insert values into the middle of list using insert_iterator" ) {
        const vector<int>     from{   2, 3, 4   };
              list<int>         to{1,          5};
        const list<int>   expected{1, 2, 3, 4, 5};

        auto insert_after = next(begin(to));
        auto output_it = inserter(to, insert_after);

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }

}


TEST_CASE( "back_inserter", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "insert values at the end of the vector" ) {
              vector<int>       to;
        const vector<int> expected{1, 2, 3};

        auto output_it = back_inserter(to);

        *output_it = 1;
        *output_it = 2;
        *output_it = 3;

        REQUIRE( expected == to );
    }

    SECTION( "insert values at the end of the vector using copy algorithm" ) {
        const vector<int>     from{1, 2, 3};
              vector<int>       to;
        const vector<int> expected{1, 2, 3};

        auto output_it = back_inserter(to);

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }

}

TEST_CASE( "front_inserter", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "insert values at the front of the dequeu" ) {
              deque<int>         to;
        const deque<int>   expected{3, 2, 1};

        auto output_it = front_inserter(to);

        *output_it = 1;
        *output_it = 2;
        *output_it = 3;

        REQUIRE( expected == to );
    }

    SECTION( "copy values from vector to list in reverse order" ) {
        const vector<int>   from{1, 2, 3};
              list<int>       to;
        const list<int> expected{3, 2, 1};

        auto output_it = front_inserter(to);

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }
    
}

