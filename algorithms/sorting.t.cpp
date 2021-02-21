#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "is_sorted", "[std] [algorithm] [sorting]" ) {
    
    SECTION( "the range is sorted" ) {
        const vector<int> vec{0, 1, 2, 2, 3, 4, 4};

        REQUIRE( is_sorted(cbegin(vec), cend(vec)) );
    } 

    SECTION( "the range is not sorted" ) {
        const vector<int> vec{0, 1, 2,   1000,   3, 4, 4};

        REQUIRE_FALSE( is_sorted(cbegin(vec), cend(vec)) );
    } 

    SECTION( "the range is sorted in descending order" ) {
        const vector<int> vec{5, 4, 3, 2, 1};

        REQUIRE( is_sorted(cbegin(vec), cend(vec), greater<int>()) );
    }

}

TEST_CASE( "is_sorted_until", "[std] [algorithm] [sorting]" ) {
    
    SECTION( "the range is sorted until 3rd element" ) {
        const vector<int> vec{5, 6, 7,   2,   3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        auto last_pos = distance(cbegin(vec), last_it);
        REQUIRE( last_pos == 3 );
        REQUIRE( *last_it == 2);
    } 

    SECTION( "the range is fully sorted" ) {
        const vector<int> vec{0, 1, 1, 2, 3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        REQUIRE( last_it == cend(vec) );
    }

    SECTION( "the range is not sorted until" ) {
        const vector<int> vec{5,   1, 2, 3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        CHECK ( last_it == next(cbegin(vec)) );
    } 

    SECTION( "the range is sorted until in descending order" ) {
        const vector<int> vec{5, 4, 3, 2,   10, 4, 9};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec), greater<int>());

        auto last_pos = distance(cbegin(vec), last_it);
        REQUIRE( last_pos == 4 );
        REQUIRE( *last_it == 10 );
    }

}

TEST_CASE( "nth_element", "[std] [algorithm] [sorting]" ) {
    
     SECTION( "set nth element in its sorted position and partition the range "
              " with first group LESS than nth element" ) {
        vector<int> vec{4, 2,   5,   3, 1, 0, 2};
        
        auto nth = begin(vec) + 2;
        REQUIRE ( *nth == 5 );

        nth_element(begin(vec), nth, end(vec));

        REQUIRE ( *nth == 2 );
        
        auto less_than_nth = [&nth](int x) { return x < *nth; };
        
        REQUIRE( all_of(begin(vec), nth, less_than_nth) );
        REQUIRE( none_of(nth, end(vec), less_than_nth) );
    } 

    SECTION( "set nth element in its sorted position and partition the range "
             "with first group GREATER than nth element" ) {
        vector<int> vec{3, 2,   5,   4, 1, 0, 2};
        
        auto nth = begin(vec) + 2;
        REQUIRE ( *nth == 5 );

        nth_element(begin(vec), nth, end(vec), greater<int>());

        REQUIRE ( *nth == 3 );
        
        auto greater_than_nth = [&nth](int x) { return x > *nth; };
        
        REQUIRE( all_of(begin(vec), nth, greater_than_nth) );
        REQUIRE( none_of(nth, end(vec), greater_than_nth) );
    } 

}

TEST_CASE( "partial_sort", "[std] [algorithm] [sorting]" ) {
    
     SECTION( "partial sort the range up to a particular position" ) {
              vector<int>      vec{4, 2, 5, 3, 1, 0, 6};
        const vector<int> expected{0, 1, 2, 3};
        
        auto middle = begin(vec) + 4;

        partial_sort(begin(vec), middle, end(vec));

        REQUIRE( equal(cbegin(expected), cend(expected), cbegin(vec)) );    
    } 

    SECTION( "partial sort the range in descending order up to a particular position" ) {
              vector<int>      vec{4, 2, 5, 3, 1, 0, 6};
        const vector<int> expected{6, 5, 4, 3};
        
        auto middle = begin(vec) + 4;

        partial_sort(begin(vec), middle, end(vec), greater<int>());

        REQUIRE( equal(cbegin(expected), cend(expected), cbegin(vec)) );    
    } 

}

TEST_CASE( "partial_sort_copy", "[std] [algorithm] [sorting]" ) {

    SECTION( "copy and partialy sort from the range which does not provide random access iterator" ) {
        const list<int>       from{4, 2, 5, 3, 1, 0, 6};
              vector<int>       to(4);
        const vector<int> expected{0, 1, 2, 3};
        
        partial_sort_copy(
              cbegin(from)
            , cend(from)
            , begin(to)
            , end(to)
        );

        REQUIRE( to == expected );    
    } 

    SECTION( "copy and partialy sort in descending order from the range which does not provide random access iterator" ) {
        const list<int>       from{4, 2, 5, 3, 1, 0, 6};
              vector<int>       to(4);
        const vector<int> expected{6, 5, 4, 3};
        
        partial_sort_copy(
              cbegin(from)
            , cend(from)
            , begin(to)
            , end(to)
            , greater<int>()
        );

        REQUIRE( to == expected );    
    }

}

TEST_CASE( "sort", "[std] [algorithm] [sorting]" ) {

    SECTION( "sort the range" ) {
              vector<int>      vec{4, 2, 5, 3, 1, 0, 6};
        const vector<int> expected{0, 1, 2, 3, 4, 5, 6};
        
        sort(begin(vec), end(vec));

        REQUIRE( vec == expected );    
    } 

    SECTION( "sort the range in descending order" ) {
              vector<int>      vec{4, 2, 5, 3, 1, 0, 6};
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};
        
        sort(begin(vec), end(vec), greater<int>());

        REQUIRE( vec == expected );    
    } 

}

// stable_sort 
struct programmer {
    string name;
    int    age;
};

bool operator==(const programmer& l, const programmer& r) { 
    return l.name == l.name && l.age == r.age;
}

TEST_CASE( "stable_sort", "[std] [algorithm] [sorting]" ) {
    
    SECTION( "sort the range by age preserving original order of the elements" ) {
        vector<programmer> vec{
              {"john",   55}
            , {"andrei", 46}
            , {"scott",  51}
            , {"herb",   51}
        };

        const vector<programmer> expected{
              {"andrei", 46}
            , {"scott",  51}
            , {"herb",   51}
            , {"john",   55}
        };

        auto sort_by_age_asc = [](const programmer& l, const programmer& r) { return l.age < r.age; }; 
        
        stable_sort(begin(vec), end(vec), sort_by_age_asc);

        REQUIRE( vec == expected ); 
    } 

    SECTION( "sort the range in descennding order by age preserving original order of the elements" ) {
        vector<programmer> vec{
              {"john",   55}
            , {"andrei", 46}
            , {"scott",  51}
            , {"herb",   51}
        };

        const vector<programmer> expected{
              {"john",   55}
            , {"scott",  51}
            , {"herb",   51}
            , {"andrei", 46}
        };

        auto sort_by_age_desc = [](const programmer& l, const programmer& r) { return l.age > r.age; }; 

        stable_sort(begin(vec), end(vec), sort_by_age_desc);

        REQUIRE( vec == expected ); 
    }

}
