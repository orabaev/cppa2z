#include <catch.hpp>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE( "copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements to empty vector using back inserter" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to;

        copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( from == to );
    } 

    SECTION( "copy inplace overlapping range" ) {
              vector<int> vec{1, 2, 3, 6, 1, 2};
        const vector<int> expected{1, 2, 3, 1, 2, 3};

        copy(cbegin(vec), cbegin(vec) + 3, begin(vec) + 3);

        REQUIRE( expected == vec );
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

TEST_CASE( "copy_backward", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy last 3 elements to the end of non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to{1, 2, 3, 4, 0, 0, 0};

        copy_backward(cbegin(from) + 4, cend(from), end(to));

        REQUIRE( from == to );
    }

}

TEST_CASE( "copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; copy all even elements to empty vector using back inserter" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to;
        const vector<int> expected{2, 4, 6};
        const auto is_even = [](int x) { return x % 2 == 0; };

        copy_if(cbegin(from), cend(from), back_inserter(to), is_even);

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "copy_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int> to{1, 2, 3, 0, 0, 6, 7};

        copy_n(cbegin(from) + 3, 2, begin(to) + 3);

        REQUIRE( from == to );
    }

}
