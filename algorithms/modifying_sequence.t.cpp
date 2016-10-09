#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

using namespace std;

TEST_CASE( "copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements to empty vector using back inserter" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to;

        copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( from == to );
    } 

    SECTION( "copy all elements to non empty vector overriding existing elements" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to(from.size());

        copy(cbegin(from), cend(from), begin(to));

        REQUIRE( from == to );
    }

    SECTION( "copy all elements to non empty vector in reverse order" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to(from.size());
        const vector<int> expected{7, 6, 5, 4, 3, 2, 1};


        auto reverse_iterator = rbegin(to);
        copy(cbegin(from), cend(from), reverse_iterator);

        REQUIRE( expected == to );
    }

    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to{1, 2, 3, 0, 0, 6, 7};

        copy(cbegin(from) + 3, cbegin(from) + 5, begin(to) + 3);

        REQUIRE( from == to );
    }

}

