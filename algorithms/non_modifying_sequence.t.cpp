#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <set>

using namespace std;

TEST_CASE( "adjacent_find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "two consecutive elements found in the range at position 2" ) {
        const vector<int> vec{0, 1,   2, 2,   4, 5, 6};

        const auto it = adjacent_find(cbegin(vec), end(vec));

        REQUIRE( it != cend(vec) );

        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 2 );
    } 

    SECTION( "determine if multiset has duplicate elements" ) {
        const multiset<int> mset{0, 1, 2,   3, 3,   4, 5};

        const auto it = adjacent_find(cbegin(mset), end(mset));
        bool has_duplicates = it != cend(mset);

        REQUIRE( has_duplicates );
        REQUIRE( *it == 3 );
    } 

    SECTION( "two consecutive upper case characters found in the range at position 3" ) {
        const string str{"aBcDEfg"};

        auto both_upper = [](char x, char y) { return isupper(x) && isupper(y); };

        const auto it = adjacent_find(cbegin(str), cend(str), both_upper);

        REQUIRE( it != cend(str) );

        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "all_of(C++11)", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "all elements in the range are even" ) {
        const vector<int> vec{2, 4, 6, 8, 10, 12, 14};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( all_of(cbegin(vec), cend(vec), is_even) );
    } 

}

TEST_CASE( "any_of(C++11)", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "some of the elements in the range are odd" ) {
        const vector<int> vec{1, 3,   16,   5, 7};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( any_of(cbegin(vec), cend(vec), is_even) );
    } 

}

TEST_CASE( "count", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "returns count of 1s in the range" ) {
        const vector<int> vec{1, 1,   2, 5,   1, 1,  6};

        REQUIRE( count(cbegin(vec), cend(vec), 1)  == 4 );
    } 

}

TEST_CASE( "count_if", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "returns number of even elements in the range" ) {
        const vector<int> vec{0, 1, 2, 3, 4, 5, 6};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( count_if(cbegin(vec), cend(vec), is_even) == 4 );
    }

}

TEST_CASE( "equal", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "two sets of elements are equal" ) {
        const vector<int> vec{1, 2, 3};
        const list<int>   lst{1, 2, 3, 4, 5};

        REQUIRE( equal(cbegin(vec), cend(vec), cbegin(lst)) );
    }

    SECTION( "two sets of elements are equal using reverse iterator" ) {
        const vector<int> vec1{0, 1, 2, 3};
        const vector<int> vec2{3, 2, 1, 0};

        const auto reverse_iterator = crbegin(vec2); 

        REQUIRE( equal(cbegin(vec1), cend(vec1), reverse_iterator) );
    }

    SECTION( "two set of elements are equal using case insensitive compare" ) {
        const string str1{"aBCd1fG"};
        const string str2{"AbCD1Fg"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };

        const bool is_equal = equal(
                                  cbegin(str1)
                                , cend(str1)
                                , cbegin(str2)
                                , case_insensitive_compare
                              );

        REQUIRE ( is_equal );
    }

    SECTION( "two set of elements are equal when using end bounds on both ranges" ) {
        const vector<int> vec1{ 0, 1,   2, 3, 4        };
        const vector<int> vec2{    7,   2, 3, 4,   5, 6};
        
        const bool is_equal = equal(
                                  cbegin(vec1) + 2
                                , cend(vec1)
                                , cbegin(vec2) + 1
                                , cbegin(vec2) + 4
                              );

        REQUIRE( is_equal );
    }

}

TEST_CASE( "find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "element with value 10 found in the range at position 3" ) {
        const vector<int> vec{0, 1, 2,   10,   4, 5, 6};

        const auto it = find(cbegin(vec), cend(vec), 10);

        REQUIRE( it != cend(vec) );

        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos  == 3 );
    }

}

TEST_CASE( "find_first_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "element from the second range found in the first range at position 1" ) {
        const vector<int> vec1{1,   2,   3, 10, 4, 5, 6};
        const vector<int> vec2{10,  2,  19};

        const auto it = find_first_of(
                              cbegin(vec1)
                            , cend(vec1)
                            , cbegin(vec2)
                            , cend(vec2)
                        );

        REQUIRE( it != cend(vec1) );

        const auto found_at_pos = distance(cbegin(vec1), it);
        REQUIRE( found_at_pos == 1 );
    }

    SECTION( "character from second string found in the first string at position 2" ) {
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
    
    SECTION( "element found in the range at position 4" ) {
        const vector<int> vec{1, 3, 5, 7,   8,   5, 6};

        auto is_even = [](int x) { return x % 2 == 0; };

        const auto it = find_if(cbegin(vec), cend(vec), is_even);

        REQUIRE( it != cend(vec) );

        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 4 );
    }

}

TEST_CASE( "find_if_not", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "find non even element" ) {
        const vector<int> vec{2, 4, 6, 8,   9,   10, 12};

        auto is_even = [](int x) { return x % 2 == 0; };

        const auto it = find_if_not(cbegin(vec), cend(vec), is_even);

        REQUIRE( it != cend(vec) );

        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 4 );
    }

}

TEST_CASE( "find_end", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "last occurence of sub sequence found in the range at position 6" ) {
        const vector<int> vec1{1, 2, 3, 1, 2, 5,   1, 2};
        const vector<int> vec2{                    1, 2};
        
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
        auto add_total = [&total](int x) { total += x; };
         
        for_each(cbegin(vec1), cend(vec1), add_total);

        REQUIRE( total == 28 );
    }
    
    SECTION( "convert all elements in the range to upper case" ) {
        string str{"hello c++"};

        auto change_to_upper = [](char& x) { x = toupper(x); };
         
        for_each(begin(str), end(str), change_to_upper);

        REQUIRE( str == "HELLO C++" );
    }

}

#ifndef __linux__
TEST_CASE( "for_each_n(C++17)", "[std] [algorithm] [non modifying]" ) {

    SECTION( "calculate total sum of first 3 elements" ) {
        const vector<int> vec1{1, 2, 3, 4, 5, 6, 7};

        int total = 0;
        auto add_total = [&total](int x) { total += x; };
        auto it_end = for_each_n(cbegin(vec1), 3, add_total);

        REQUIRE( total == 6 );
        REQUIRE( it_end == cbegin(vec1) + 3 );
    }
    
    SECTION( "convert first 3 elements in the range to upper case" ) {
        string str{"hello c++"};

        auto change_to_upper = [](char& x) { x = toupper(x); };
         
        for_each_n(begin(str), 3, change_to_upper);

        REQUIRE( str == "HELlo c++" );
    }

}
#endif

TEST_CASE( "mismatch", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "return the frirst mismatching pair of elements from two ranges" ) {
        const vector<int> vec1{1, 3, 5,   0,   1};
        const vector<int> vec2{1, 3, 5,   4,   2};

        const auto pr = mismatch(cbegin(vec1), cend(vec1), cbegin(vec2));
        
        REQUIRE( *pr.first  == 0 );
        REQUIRE( *pr.second == 4 );
    } 

    SECTION( "return the frirst summed non even pair of elements from two ranges" ) {
        const vector<int> vec1{1, 3,   2,   2,  1};
        const vector<int> vec2{1, 5,   5,   4,  1};
        
        auto sum_is_even = [](const int x, const int y) { return (x + y) % 2 == 0; };

        const auto pr = mismatch(
                              cbegin(vec1)
                            , cend(vec1)
                            , cbegin(vec2)
                            , sum_is_even
                        );
        
        REQUIRE( *pr.first  == 2);
        REQUIRE( *pr.second == 5);
    }

    SECTION( "return the first mismatching pair of elements from two ranges of different size" ) {
        const vector<int> vec1{1, 3, 5,   4,   1};
        const vector<int> vec2{1, 3, 5};
        
        const auto pr = mismatch(
                              cbegin(vec1)
                            , cend(vec1)
                            , cbegin(vec2)
                            , cend(vec2)
                        );
        
        REQUIRE( *pr.first == 4 );
        REQUIRE( pr.second == cend(vec2) );
    }

}

TEST_CASE( "none_of(C++11)", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "none of elements in the range match" ) {
        const vector<int> vec{1, 3, 5, 7, 9};

        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( none_of(cbegin(vec), cend(vec), is_even) );
    } 

}

TEST_CASE( "search", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "first occurence of sub sequence found in the range at position 3" ) {
        const vector<int> vec1{2, 2, 3,   1, 2,   5, 1, 2};
        const vector<int> vec2{           1, 2           };
        
        const auto it = search(
                              cbegin(vec1)
                            , cend(vec1)
                            , cbegin(vec2)
                            , cend(vec2)
                        );

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
        const string str{"AAbbccAAAAbbccc"};
        
        const size_t count{4};
        const char   value{'A'};

        const auto it = search_n(
                                cbegin(str)
                              , cend(str)
                              , count
                              , value
                        );

        REQUIRE( it != cend(str) );

        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 6 );
    }

    SECTION( "3 consecutive even numbers  found in the range at position 2" ) {
        const vector<int> vec{1, 3,   4, 2, 8,   5, 7};

        const size_t count{3};
        const int    value{2};

        auto divisible_by_value = [](int x, int v) { return x % v == 0; };

        const auto it = search_n(
                              cbegin(vec)
                            , cend(vec)
                            , count
                            , value
                            , divisible_by_value
                        );

        REQUIRE( it != cend(vec) );

        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 2 );
    }

}
