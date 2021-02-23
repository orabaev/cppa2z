#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <random>

using namespace std;

TEST_CASE( "copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements to empty vector using back inserter" ) {
        const vector<int> from{0, 1, 2, 3, 4, 5, 6};
              vector<int>   to;

        copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( from == to );
    } 

    SECTION( "copy inplace overlapping range" ) {
              vector<int>      vec{1, 2, 3,   6, 1, 2}; 
        const vector<int> expected{1, 2, 3,   1, 2, 3}; 

        copy(cbegin(vec), cbegin(vec) + 3, begin(vec) + 3);

        REQUIRE( vec == expected );
    }

    SECTION( "copy all elements to non empty vector overriding existing elements" ) {
        const vector<int> from{0, 1, 2, 3, 4, 5, 6};
              vector<int>   to(from.size());

        copy(cbegin(from), cend(from), begin(to));

        REQUIRE( from == to );
    }

    SECTION( "copy all elements to non empty vector in reverse order" ) {
        const vector<int>     from{0, 1, 2, 3, 4, 5, 6};
              vector<int>       to(from.size());
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};

        auto reverse_iterator = rbegin(to);
        copy(cbegin(from), cend(from), reverse_iterator);

        REQUIRE( to == expected );
    }

    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{0, 1, 2,   3, 4,   5, 6};
              vector<int>   to{0, 1, 2,   0, 0,   5, 6};

        copy(cbegin(from) + 3, cbegin(from) + 5, begin(to) + 3);

        REQUIRE( from == to );
    }

}

TEST_CASE( "copy_backward", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy last 3 elements to the end of non empty vector" ) {
        const vector<int> from{1, 2, 3, 4,   5, 6, 7};
              vector<int>   to{1, 2, 3, 4,   0, 0, 0};

        copy_backward(cbegin(from) + 4, cend(from), end(to));

        REQUIRE( from == to );
    }

}

TEST_CASE( "copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; copy all even elements to empty vector using back inserter" ) {
        const vector<int>     from{1, 2, 3, 4, 5, 6, 7};
              vector<int>       to;
        const vector<int> expected{2, 4, 6};

        auto is_even = [](int x) { return x % 2 == 0; };

        copy_if(cbegin(from), cend(from), back_inserter(to), is_even);

        REQUIRE( to == expected );
    } 

}

TEST_CASE( "copy_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{0, 1, 2,   3, 4,   5, 6};
              vector<int>   to{0, 1, 2,   0, 0,   5, 6};

        copy_n(cbegin(from) + 3, 2, begin(to) + 3);

        REQUIRE( from == to );
    }

}

TEST_CASE( "fill", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "assign 1 to the elements in the range" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5, 6};
        const vector<int> expected{1, 1, 1, 1, 1, 1, 1};

        fill(begin(vec), end(vec), 1);

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "fill_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "assign 0 to the first 3 elements in the range" ) {
              vector<int>      vec{1, 2, 3,   4, 5, 6, 7};
        const vector<int> expected{0, 0, 0,   4, 5, 6, 7};

        const auto it = fill_n(begin(vec), 3, 0);

        REQUIRE( expected == vec );

        REQUIRE( *it == 4 );
    }

}

TEST_CASE( "generate", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "initialize vector with incrementing values from 0 to 6" ) {
              vector<int>      vec(7);
        const vector<int> expected{0, 1, 2, 3, 4, 5, 6};

        int i = 0; 
        auto increment = [&i]() { return i++; };

        generate(begin(vec), end(vec), increment);

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "generate_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "add 4 incremented elements at the end of the vector" ) {
              vector<int>      vec{0, 1, 2};
        const vector<int> expected{0, 1, 2,   3, 4, 5, 6};

        int i = vec.back(); 
        auto increment = [&i]() { return ++i; };

        generate_n(back_inserter(vec), 4, increment);

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "iter_swap", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "swap values of first and last elements in the vector" ) {
              vector<int>      vec{0,   1, 2, 3, 4, 5,   6};
        const vector<int> expected{6,   1, 2, 3, 4, 5,   0};

        iter_swap(begin(vec), rbegin(vec));

        REQUIRE( vec == expected );
    }

    SECTION( "reverse string" ) {
              string      str{"abcdefg"};
        const string expected{"gfedcba"};

        auto left = begin(str);
        auto right = --end(str);
        while (left < right) iter_swap(left++, right--);

        REQUIRE( str == expected );
    }

}

TEST_CASE( "move", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "move strings from one vector to another" ) {
        const vector<string>     from{"hello", "C++"};
              vector<string>       to(from.size());
        const vector<string> expected{"hello", "C++"};

        move(begin(from), end(from), begin(to));

        REQUIRE( to == expected );
        // DO NOT RELY ON VALUES OF SOURCE RANGE
        // AFTER THEY HAVE BEEN MOVED FROM
    }

}

TEST_CASE( "move_backward", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "shift and set; insert new string at the begining of the vector" ) {
              vector<string>      vec{"hello", "C++"};
        const vector<string> expected{"Hi", "hello", "C++"};

        vec.resize(vec.size() + 1);
        move_backward(begin(vec), --end(vec), end(vec));
        vec.front() = "Hi";        

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "remove", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "remove elements with value 1 from the vector" ) {
              vector<int>      vec{1,   2, 5,   1,   7, 5, 6,   1};
        const vector<int> expected{2, 5, 7, 5, 6};

        auto erase_it = remove(begin(vec), end(vec), 1); 
        vec.erase(erase_it, vec.end());

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "remove_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; remove even elements from the vector" ) {
              vector<int>      vec{1,   2, 4,   7, 5,   6,   3};
        const vector<int> expected{1, 7, 5, 3};

        auto is_even = [](int x) { return x % 2 == 0; };

        auto erase_it = remove_if(begin(vec), end(vec), is_even); 
        vec.erase(erase_it, vec.end());

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "remove_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all characters from one string to another excluding space" ) {
        const string     from{"H E L L O"};
              string       to{"     "};
        const string expected{"HELLO"};

        remove_copy(cbegin(from), cend(from), begin(to), ' '); 

        REQUIRE( to == expected );
    }

}

TEST_CASE( "remove_copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; copy all elements from one vector to another excluding even numbers" ) {
        const vector<int>     from{1,   2, 4,   7, 5,   6,   3};
              vector<int>       to;
        const vector<int> expected{1, 7, 5, 3};

        auto is_even = [](int x) { return x % 2 == 0; };

        remove_copy_if(cbegin(from), cend(from), back_inserter(to), is_even); 

        REQUIRE( to == expected );
    }

}

TEST_CASE( "replace", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "replace all 1s with 0s" ) {
              vector<int>      vec{1,   2,   1, 1,   3, 6,   1};
        const vector<int> expected{0,   2,   0, 0,   3, 6,   0};

        replace(begin(vec), end(vec), 1, 0); 

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "replace_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "replace all even numbers with 1" ) {
              vector<int>      vec{3,   2,   7,   8, 0, 6,   5};
        const vector<int> expected{3,   1,   7,   1, 1, 1,   5};

        auto is_even = [](int x) { return x % 2 == 0; };
        int replace_to = 1;

        replace_if(begin(vec), end(vec), is_even, replace_to); 

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "replace_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements from one vector to another replacing all 1s with 0s" ) {
        const vector<int>     from{1,   2,   1, 1,   3, 6,   1};
              vector<int>       to;
        const vector<int> expected{0,   2,   0, 0,   3, 6,   0};

        int replace_from = 1;
        int replace_to   = 0;

        replace_copy(
              cbegin(from)
            , cend(from)
            , back_inserter(to)
            , replace_from
            , replace_to
        ); 

        REQUIRE( to == expected );
    }

}

TEST_CASE( "replace_copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements from one vector to another replacing all even numbers with 1" ) {
        const vector<int>      from{3,   2,   7,   8, 0, 6,   5};
              vector<int>        to;
        const vector<int>  expected{3,   1,   7,   1, 1, 1,   5};

        auto is_even = [](int x) { return x % 2 == 0; };
        int replace_to  = 1;

        replace_copy_if(
              cbegin(from)
            , cend(from)
            , back_inserter(to)
            , is_even
            , replace_to
        ); 

        REQUIRE( to == expected );
    }

}

TEST_CASE( "reverse", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reverse elements in the range" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5, 6};
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};

        reverse(begin(vec), end(vec));

        REQUIRE( vec == expected );
    }

}

TEST_CASE( "reverse_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reverse elements in the destination range" ) {
        const vector<int>     from{0, 1, 2, 3, 4, 5, 6};
              vector<int>       to;
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};

        reverse_copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( to == expected );
    }

}

TEST_CASE( "rotate", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "rotate first 2 elements to the end" ) {
              vector<int>      vec{0, 1,    2, 3, 4, 5, 6};
        const vector<int> expected{2, 3, 4, 5, 6,    0, 1};

        auto first  = begin(vec);
        auto middle = begin(vec) + 2;
        auto last   = end(vec); 

        const auto it = rotate(first, middle, last);

        REQUIRE( vec == expected );
    }

    SECTION( "rotate last 2 elements to the front" ) {
              vector<int>      vec{0, 1, 2, 3, 4,   5, 6};
        const vector<int> expected{5, 6,   0, 1, 2, 3, 4};

        auto first  = begin(vec);
        auto middle = end(vec) - 2;
        auto last   = end(vec); 

        const auto it = rotate(first, middle, last);

        REQUIRE( vec == expected );
    }

    SECTION( "rotate 2nd and 3rd elements with 4th and 5th elements" ) {
              vector<int>      vec{0,   1, 2,   3, 4,   5};
        const vector<int> expected{0,   3, 4,   1, 2,   5};

        auto first  = begin(vec) + 1;
        auto middle = begin(vec) + 3;
        auto last   = end(vec)   - 1; 

        const auto it = rotate(first, middle, last);

        REQUIRE( vec == expected );
    }
}

TEST_CASE( "shuffle", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reorder elements in the container based on the provided random function generator" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> original{vec};

        REQUIRE( original == vec );

        auto engine = default_random_engine{};

        shuffle(begin(vec), end(vec), engine);

        REQUIRE( original != vec );
    }

}

TEST_CASE( "swap", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "swaps values" ) {
        int x = 1;
        int y = 2;

        swap(x, y);

        REQUIRE( 2 == x );
        REQUIRE( 1 == y );
    }

    SECTION( "use swap to set the object to a default constructed state" ) {
        vector<int>          vec{0, 1, 2};
        vector<int> empty_vector;
    
        swap(vec,  empty_vector);
        
        REQUIRE( vec.empty() ); 

    }

}

TEST_CASE( "swap_ranges", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "exchange elements between two ranges" ) {
              vector<int>          vec{0, 1, 2};
        const vector<int> expected_vec{3, 4, 5};

              list<int>            lst{3, 4, 5};
        const list<int>   expected_lst{0, 1, 2};

        swap_ranges(begin(vec), end(vec), begin(lst));

        REQUIRE( vec == expected_vec );
        REQUIRE( lst == expected_lst );
    }

}

TEST_CASE( "transform", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "convert in place all elements to upper case" ) {
              string      str("hello world");
        const string expected("HELLO WORLD");

        auto to_upper = [](char x) { return toupper(x); };

        const auto it = transform(
                             begin(str)
                           , end(str)
                           , begin(str)
                           , to_upper
                        );

        REQUIRE( str == expected );
        REQUIRE( it == cend(str) );
    }

    SECTION( "sum each element from different containers and store results in another container" ) {
        const vector<int>     vec1{1, 2, 3 ,4, 5};
        const vector<int>     vec2{5, 4, 3, 2, 1};
        const vector<int> expected{6, 6, 6, 6, 6};
              vector<int>   result(expected.size());

        auto sum = [](int x, int y) { return x + y; };

        const auto it = transform(
                             cbegin(vec1)
                           , cend(vec1)
                           , cbegin(vec2)
                           , begin(result)
                           , sum 
                        );

        REQUIRE( result == expected );
        REQUIRE( it == cend(result) );
    }

}

TEST_CASE( "unique", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "remove duplicate consecutive elements and then erase the duplicates" ) {
              vector<int>      vec{1, 1,  2, 2, 2, 2,  3, 3, 3,  1, 1, 1, 1};
        const vector<int> expected{1, 2, 3, 1};

        const auto it = unique(begin(vec), end(vec));

        vec.erase(it, end(vec));

        REQUIRE( vec == expected );
    }

    SECTION( "remove consecutive spaces" ) {
              string      str{"hello     world  C++    14"};
        const string expected{"hello world C++ 14"};

        auto both_spaces = [](char x, char y) { return isspace(x) && isspace(y); };

        const auto it = unique(begin(str), end(str), both_spaces);

        str.erase(it, end(str));

        REQUIRE( str == expected );
    }

}

TEST_CASE( "unique_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy unique consecutive elements" ) {
        const vector<int>     from{1, 1, 2, 2, 2, 2, 3, 3, 3, 1, 1, 1, 1};
              vector<int>       to;
        const vector<int> expected{1, 2, 3, 1};

        unique_copy(cbegin(from) , cend(from) , back_inserter(to));

        REQUIRE( to == expected );
    }

    SECTION( "copy string while removing consecutive spaces" ) {
        const string     from{"hello     world  C++    14"};
              string       to;
        const string expected{"hello world C++ 14"};

        auto both_spaces = [](char x, char y) { return isspace(x) && isspace(y); };

        unique_copy(
              cbegin(from)
            , cend(from)
            , back_inserter(to)
            , both_spaces
        );

        REQUIRE( to == expected );
    }

}
