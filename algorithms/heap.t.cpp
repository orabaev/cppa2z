#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

TEST_CASE( "is_heap", "[std] [algorithm] [heap]" ) {
    
    // max heap

    SECTION( "elements in the range are max heap" ) {
        vector<int> vec{5, 4, 3, 2, 1};

        REQUIRE( is_heap(cbegin(vec), cend(vec)) );
    }

    SECTION( "elements in the empty range are max heap" ) {
        const vector<int> vec;

        REQUIRE( is_heap(cbegin(vec), cend(vec)) );
    }

    SECTION( "elements in the range are not max heap" ) {
        const vector<int> vec{1, 5, 3, 2, 4};

        REQUIRE_FALSE( is_heap(cbegin(vec), cend(vec)) );
    }

    // min heap

    SECTION( "elements in the range are min heap" ) {
        vector<int> vec{1, 2, 3, 4, 5};

        REQUIRE( is_heap(cbegin(vec), cend(vec), greater<int>()) );
    }

    SECTION( "elements in the empty range are min heap" ) {
        const vector<int> vec;

        REQUIRE( is_heap(cbegin(vec), cend(vec), greater<int>()) );
    }

    SECTION( "elements in the range are not min heap" ) {
        const vector<int> vec{7, 5, 3, 2, 4};

        REQUIRE_FALSE( is_heap(cbegin(vec), cend(vec), greater<int>()) );
    }

}

TEST_CASE( "is_heap_until", "[std] [algorithm] [heap]" ) {
    
    // max heap

    SECTION( "returns last iterator of the empty max heap" ) {
        const vector<int> vec;

        const auto last = is_heap_until(cbegin(vec), cend(vec));

        REQUIRE( last == cend(vec) );
    }

    SECTION( "returns last iterator where range is not max heap" ) {
        const vector<int> vec {1,   5,   3, 2, 4};

        const auto last = is_heap_until(cbegin(vec), cend(vec));

        REQUIRE( last == next(cbegin(vec)) );
        REQUIRE( *last == 5 );

    }

    SECTION( "return last iterator of the complete max heap" ) {
        vector<int> vec {5, 4, 3, 2, 1};

        const auto last = is_heap_until(cbegin(vec), cend(vec));
        REQUIRE( last == cend(vec) );
    }

    SECTION( "returns last iterator of the partial max heap" ) {
        vector<int> vec {5, 4, 3,   10,   100};

        const auto last = is_heap_until(cbegin(vec), cend(vec));
        REQUIRE( last != cend(vec) );

        const auto last_pos = distance(cbegin(vec), last);
        REQUIRE( last_pos == 3  );
   }

   // min heap

   SECTION( "returns last iterator of the empty min heap" ) {
        const vector<int> vec;

        const auto last = is_heap_until(cbegin(vec), cend(vec), greater<int>());

        REQUIRE( last == cend(vec) );
    }

    SECTION( "returns last iterator where range is not min heap" ) {
        const vector<int> vec {5,   1,   3, 2, 4};

        const auto last = is_heap_until(cbegin(vec), cend(vec), greater<int>());

        REQUIRE( last == next(cbegin(vec)) );
        REQUIRE( *last == 1);

    }

    SECTION( "return last iterator of the complete min heap" ) {
        vector<int> vec {1, 2, 3, 4, 5};

        const auto last = is_heap_until(cbegin(vec), cend(vec), greater<int>());

        REQUIRE( last == cend(vec) );
    }

    SECTION( "returns last iterator of the partial min heap" ) {
        vector<int> vec {3, 4, 5,   2,   1};

        const auto last = is_heap_until(cbegin(vec), cend(vec), greater<int>());

        REQUIRE( last != cend(vec) );

        const auto last_pos = distance(cbegin(vec), last);
        REQUIRE( last_pos == 3 );
   }

}

TEST_CASE( "make_heap", "[std] [algorithm] [heap]" ) {
    
    SECTION( "transform range into a max heap" ) {
        vector<int> vec{1, 5, 3, 2, 4};

        make_heap(begin(vec), end(vec));

        REQUIRE( is_heap(cbegin(vec), cend(vec)) );
    }

    SECTION( "transform range into a min heap" ) {
        vector<int> vec{7, 5, 3, 2, 4};

        make_heap(begin(vec), end(vec), greater<int>());

        REQUIRE( is_heap(cbegin(vec), cend(vec), greater<int>()) );
    }

}

TEST_CASE( "push_heap", "[std] [algorithm] [heap]" ) {
    
    SECTION( "add elements to the vector while applying push_heap operation to make it a max heap" ) {
        vector<int> vec;

        vec.push_back(4);
        push_heap(begin(vec), end(vec));

        REQUIRE ( vec.front() == 4 );
        REQUIRE( is_heap(cbegin(vec), cend(vec)) );


        vec.push_back(1);
        push_heap(begin(vec), end(vec));

        REQUIRE ( vec.front() == 4 );
        REQUIRE( is_heap(cbegin(vec), cend(vec)) );


        vec.push_back(7);
        push_heap(begin(vec), end(vec));

        REQUIRE ( vec.front() == 7 );
        REQUIRE( is_heap(cbegin(vec), cend(vec)) );
    }

}

TEST_CASE( "pop_heap", "[std] [algorithm] [heap]" ) {
    
    SECTION( "move largest element to the back of the range "
             "maintaining max heap property for the rest of the elements" ) {
        vector<int> vec{9, 7, 5, 1};

        pop_heap(begin(vec), end(vec));
        REQUIRE( vec.back() == 9 ); 

        vec.pop_back();
        REQUIRE( is_heap(cbegin(vec), cend(vec)) );
    }

    SECTION( "convert the max heap into a sorted range in ascending order using pop_heap operation" ) {
              vector<int>      vec{5, 1, 9, 7};
        const vector<int>   sorted{1, 5, 7, 9};

        make_heap(begin(vec), end(vec));
        
        const auto b = begin(vec);
        auto e = end(vec);
        while (b < e) pop_heap(b, e--);

        REQUIRE( vec == sorted );
    }

    SECTION( "move smallest element to the back of the vector "
             "maintaining max heap property for the rest of the elements" ) {
        vector<int> vec{9, 5, 1, 7};

        make_heap(begin(vec), end(vec), greater<int>());
        
        pop_heap(begin(vec), end(vec), greater<int>());
        REQUIRE( vec.back() == 1 ); 

        vec.pop_back();
        REQUIRE( is_heap(cbegin(vec), cend(vec), greater<int>()) );
    }

}

TEST_CASE( "sort_heap", "[std] [algorithm] [heap]" ) {

    SECTION( "convert the max heap into a sorted range in ascending order" ) {
               vector<int>      vec{5, 1, 9, 7};
        const vector<int>   sorted{1, 5, 7, 9};
        
        make_heap(begin(vec), end(vec));
        sort_heap(begin(vec), end(vec));

        REQUIRE( vec == sorted );
    }

    SECTION( "convert the min heap into a sorted range in descending order" ) {
              vector<int>      vec{5, 1, 9, 7};
        const vector<int>   sorted{9, 7, 5, 1};
        
        make_heap(begin(vec), end(vec), greater<int>());
        sort_heap(begin(vec), end(vec), greater<int>());

        REQUIRE( vec == sorted );
    }

}
