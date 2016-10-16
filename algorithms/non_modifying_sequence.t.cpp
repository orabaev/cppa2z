#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

using namespace std;

TEST_CASE( "adjacent_find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "two consecutive elements found in the range at position 2" ) {
        const vector<int> vec{1, 2, 3, 3, 5, 6, 7};

        const auto it = adjacent_find(cbegin(vec), cend(vec));

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 2 );
    } 

    SECTION( "using predicates; two consecutive upper case characters found in the range at position 3" ) {
        const string str{"aBcDEfg"};

        auto both_upper = [](char x, char y) { return isupper(x) && isupper(y); };

        const auto it = adjacent_find(cbegin(str), cend(str), both_upper);

        REQUIRE( it != cend(str) );
        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "all_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicates; all elements in the range match" ) {
        const vector<int> vec{2, 4, 6, 8, 10, 12, 14};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( all_of(cbegin(vec), cend(vec), is_even) );
    } 

}

TEST_CASE( "any_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "some of the elements in the range match" ) {
        const vector<int> vec{1, 2, 3, 2, 5, 6, 7};

        auto is_one = [](int x) { return x == 1; };

        REQUIRE( any_of(cbegin(vec), cend(vec), is_one) );
    } 

}

TEST_CASE( "count", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "returns number of 1s in the range" ) {
        const vector<int> vec{1, 1, 2, 5, 1, 1, 6};

        REQUIRE( 4 == count(cbegin(vec), cend(vec), 1) );
    } 

}

TEST_CASE( "count_if", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicates; returns number of even numbers in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5, 6, 7};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( 3 == count_if(cbegin(vec), cend(vec), is_even) );
    }

}

TEST_CASE( "equal", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "start from the begining; two ranges are equal; comparing vector and list" ) {
        const vector<int> vec{1, 2, 3, 4, 5, 6, 7};
        const list<int>   lst{1, 2, 3, 4, 5, 6, 7};

        REQUIRE( equal(cbegin(vec), cend(vec), cbegin(lst)) );
    }

    SECTION( "using reverse iterator; two ranges are equal" ) {
        const vector<int> vec1{1, 2, 3, 4, 5, 6, 7};
        const vector<int> vec2{7, 6, 5, 4, 3, 2, 1};

        const auto reverse_iterator = crbegin(vec2); 

        REQUIRE( equal(cbegin(vec1), cend(vec1), reverse_iterator) );
    }

    SECTION( "using predicates; two ranges are equal" ) {
        const string str1{"aBCd1fG"};
        const string str2{"AbCD1Fg"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };

        REQUIRE( equal(cbegin(str1), cend(str1), cbegin(str2), case_insensitive_compare) );
    }

}

TEST_CASE( "equal C++14", "[c++14] [std] [algorithm] [non modifying]" ) {

    SECTION( "second range; two ranges are equal;" ) {
        const vector<int> vec1{-1, 0, 1, 2, 3};
        const vector<int> vec2{0, 1, 2, 3, 4, 5, 6};
        
        const auto start1 = cbegin(vec1) + 2;
        const auto end1   = cend(vec1);
        const auto start2 = cbegin(vec2) + 1; 
        const auto end2   = cbegin(vec2) + 4;

        REQUIRE( equal(start1, end1, start2, end2) );
    }

}

TEST_CASE( "find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "element found in the range at position 3" ) {
        const vector<int> vec{1, 2, 3, 10, 4, 5, 6};

        const auto it = find(cbegin(vec), cend(vec), 10);

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "find_first_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "element from the second range found in the first range at position 1" ) {
        const vector<int> vec1{1, 2, 3, 10, 4, 5, 6};
        const vector<int> vec2{10, 2, 19};

        const auto it = find_first_of(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2));

        REQUIRE( it != cend(vec1) );
        const auto found_at_pos = distance(cbegin(vec1), it);
        REQUIRE( found_at_pos == 1 );
    }

    SECTION( "using predicate; element from the second range found in the first range at position at position 2" ) {
        const string str1{"Hello"};
        const string str2{"LOL"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };

        const auto it = find_first_of(
                              cbegin(str1)
                            , cend(str1)
                            , cbegin(str2)
                            , cend(str2)
                            , case_insensitive_compare
                        );

        REQUIRE( it != cend(str1) );
        const auto found_at_pos = distance(cbegin(str1), it);
        REQUIRE( found_at_pos == 2 );
    }

}

TEST_CASE( "find_if", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicate; element found in the range at position 4" ) {
        const vector<int> vec{1, 3, 5, 7, 8, 5, 6};

        auto is_even = [](int x) { return x % 2 == 0; };

        const auto it = find_if(cbegin(vec), cend(vec), is_even);

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 4 );
    }

}

TEST_CASE( "find_if_not", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicate; element found in the range at position 4" ) {
        const vector<int> vec{2, 4, 6, 8, 9, 10, 12};

        auto is_even = [](int x) { return x % 2 == 0; };

        const auto it = find_if_not(cbegin(vec), cend(vec), is_even);

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 4 );
    }

}

// @OPINION find_end name is confusing, it should have been called search_end
TEST_CASE( "find_end", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "last occurence of sub sequence found in the range at position 6" ) {
        const vector<int> vec1{1, 2, 3, 1, 2, 5, 1, 2};
        const vector<int> vec2{1, 2};
        
        const auto it = find_end(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2));

        REQUIRE( it != cend(vec1) );
        const auto found_at_pos = distance(cbegin(vec1), it);
        REQUIRE( found_at_pos == 6 );
    }

    SECTION( "last occurence of sub sequence found in the range at position 3" ) {
        const string str1{"abCabDer"};
        const string str2{"AB"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };
        
        const auto it = find_end(
                              cbegin(str1)
                            , cend(str1)
                            , cbegin(str2)
                            , cend(str2)
                            , case_insensitive_compare
                        );

        REQUIRE( it != cend(str1) );
        const auto found_at_pos = distance(cbegin(str1), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "for_each", "[std] [algorithm] [non modifying]" ) {

    SECTION( "calculate total sum of all elements" ) {
        const vector<int> vec1{1, 2, 3, 4, 5, 6, 7};

        int total = 0;
        auto sum = [&total](int x) { total += x; };
         
        for_each(cbegin(vec1), cend(vec1), sum);

        REQUIRE( total == 28 );
    }
    
    SECTION( "convert all elements in the range to upper case" ) {
        string str{"hello c++"};

        auto change_to_upper = [](char& x) { x = toupper(x); };
         
        for_each(begin(str), end(str), change_to_upper);

        REQUIRE( str == "HELLO C++" );
    }

}

TEST_CASE( "search", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "first occurence of sub sequence found in the range at position 3" ) {
        const vector<int> vec1{2, 2, 3, 1, 2, 5, 1, 2};
        const vector<int> vec2{1, 2};
        
        const auto it = search(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2));

        REQUIRE( it != cend(vec1) );
        const auto found_at_pos = distance(cbegin(vec1), it);
        REQUIRE( found_at_pos == 3 );
    }

    SECTION( "first occurence of sub sequence found in the range at position 0" ) {
        const string str1{"abCabDer"};
        const string str2{"AB"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };
        
        const auto it = search(
                              cbegin(str1)
                            , cend(str1)
                            , cbegin(str2)
                            , cend(str2)
                            , case_insensitive_compare
                        );

        REQUIRE( it != cend(str1) );
        const auto found_at_pos = distance(cbegin(str1), it);
        REQUIRE( found_at_pos == 0 );
    }

}

TEST_CASE( "search_n", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "4 consecutive 'a' characters found in the range at position 6" ) {
        const string str{"aabbccaaaabbbccc"};
        
        const auto it = search_n(cbegin(str), cend(str), 4, 'a');

        REQUIRE( it != cend(str) );
        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 6 );
    }

    SECTION( "2 consecutive 'a' characters found in the range at position 0" ) {
        const string str{"aabbccaaaabbbccc"};
        
        const auto it = search_n(cbegin(str), cend(str), 2, 'a');

        REQUIRE( it != cend(str) );
        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 0 );
    }

    SECTION( "using predicates; 3 consecutive even numbers  found in the range at position 2" ) {
        const vector<int> vec{1, 3, 4, 2, 8, 6, 7};

        auto both_even = [](int x, int y) { return x % 2 == y % 2; };

        const auto it = search_n(cbegin(vec), cend(vec), 3, 2, both_even);

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 2 );
    }

}
