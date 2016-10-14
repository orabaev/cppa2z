#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

TEST_CASE( "copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements to empty vector using back inserter" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int>   to;

        copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( from == to );
    } 

    SECTION( "copy inplace overlapping range" ) {
        vector<int>            vec{1, 2, 3, 6, 1, 2}; 
        const vector<int> expected{1, 2, 3, 1, 2, 3}; 

        copy(cbegin(vec), cbegin(vec) + 3, begin(vec) + 3);

        REQUIRE( expected == vec );
    }

    SECTION( "copy all elements to non empty vector overriding existing elements" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int>   to(from.size());

        copy(cbegin(from), cend(from), begin(to));

        REQUIRE( from == to );
    }

    SECTION( "copy all elements to non empty vector in reverse order" ) {
        const vector<int>     from{1, 2, 3, 4, 5, 6, 7};
              vector<int>       to(from.size());
        const vector<int> expected{7, 6, 5, 4, 3, 2, 1};

        auto reverse_iterator = rbegin(to);
        copy(cbegin(from), cend(from), reverse_iterator);

        REQUIRE( expected == to );
    }

    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int>   to{1, 2, 3, 0, 0, 6, 7};

        copy(cbegin(from) + 3, cbegin(from) + 5, begin(to) + 3);

        REQUIRE( from == to );
    }

}

TEST_CASE( "copy_backward", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy last 3 elements to the end of non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int>   to{1, 2, 3, 4, 0, 0, 0};

        copy_backward(cbegin(from) + 4, cend(from), end(to));

        REQUIRE( from == to );
    }

}

TEST_CASE( "copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; copy all even elements to empty vector using back inserter" ) {
        const vector<int>     from{1, 2, 3, 4, 5, 6, 7};
              vector<int>       to;
        const vector<int> expected{2, 4, 6};

        const auto is_even = [](int x) { return x % 2 == 0; };

        copy_if(cbegin(from), cend(from), back_inserter(to), is_even);

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "copy_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy 2 elements from/to position 3 to non empty vector" ) {
        const vector<int> from{1, 2, 3, 4, 5, 6, 7};
              vector<int>   to{1, 2, 3, 0, 0, 6, 7};

        copy_n(cbegin(from) + 3, 2, begin(to) + 3);

        REQUIRE( from == to );
    }

}

TEST_CASE( "fill", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "assign 1 to the elements in the range" ) {
              vector<int>      vec{1, 2, 3, 4, 5, 6, 7};
        const vector<int> expected{1, 1, 1, 1, 1, 1, 1};

        fill(begin(vec), end(vec), 1);

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "fill_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "assign 0 to the first 3 elements in the range" ) {
              vector<int>      vec{1, 2, 3, 4, 5, 6, 7};
        const vector<int> expected{0, 0, 0, 4, 5, 6, 7};

        const auto it = fill_n(begin(vec), 3, 0);

        REQUIRE( expected == vec );

        REQUIRE( 4 == *it );
    }

}

TEST_CASE( "generate", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "initialize vector with incrementing values from 1 to 7" ) {
              vector<int>      vec(7);
        const vector<int> expected{1, 2, 3, 4, 5, 6, 7};

        int i = 1; 
        const auto increment = [&i]() { return i++; };

        generate(begin(vec), end(vec), increment);

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "generate_n", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "add 4 incremented elements at the end of the vector" ) {
              vector<int>      vec{1, 2, 3};
        const vector<int> expected{1, 2, 3, 4, 5, 6, 7};

        int i = vec.back(); 
        const auto increment = [&i]() { return ++i; };

        generate_n(back_inserter(vec), 4, increment);

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "iter_swap", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "swap values of first and last elements in the vector" ) {
        vector<int>      vec{1, 2, 3, 4, 5, 6, 7};
        vector<int> expected{7, 2, 3, 4, 5, 6, 1};

        iter_swap(begin(vec), rbegin(vec));

        REQUIRE( expected == vec );
    }

    SECTION( "reverse string" ) {
        string      str{"abcdefg"};
        string expected{"gfedcba"};

        auto left = begin(str);
        auto right = --end(str);

        while (left < right) {
            iter_swap(left, right); 
            ++left; 
            --right;
        }

        REQUIRE( expected == str );
    }

}

TEST_CASE( "move", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "move strings from one vector to another" ) {
        vector<string>     from{"hello", "C++"};
        vector<string>       to(from.size());
        vector<string> expected{"hello", "C++"};

        move(begin(from), end(from), begin(to));

        REQUIRE( expected == to );
        // DO NOT RELY ON VALUES OF SOURCE RANGE
        // AFTER THEY HAVE BEEN MOVED FROM
    }

}

TEST_CASE( "move_backward", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "shift and set; insert new string at the begining of the vector" ) {
        vector<string>      vec{"hello", "C++"};
        vector<string> expected{"Hi", "hello", "C++"};

        vec.resize(vec.size() + 1);
        move_backward(begin(vec), --end(vec), end(vec));
        vec.front() = "Hi";        

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "remove", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "remove elements with value 1 from the vector" ) {
              vector<int>      vec{1, 2, 1, 7, 5, 6, 1};
        const vector<int> expected{2, 7, 5, 6};

        auto erase_it = remove(begin(vec), end(vec), 1); 
        vec.erase(erase_it, vec.end());

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "remove_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; remove even elements from the vector" ) {
              vector<int>      vec{1, 2, 4, 7, 5, 6, 3};
        const vector<int> expected{1, 7, 5, 3};

        const auto is_even = [](int x) { return x % 2 == 0; };

        auto erase_it = remove_if(begin(vec), end(vec), is_even); 
        vec.erase(erase_it, vec.end());

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "remove_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all characters from one string to another excluding space" ) {
        const string     from{"H E L L O"};
              string       to{"     "};
        const string expected{"HELLO"};

        remove_copy(cbegin(from), cend(from), begin(to), ' '); 

        REQUIRE( expected == to );
    }

}

TEST_CASE( "remove_copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "using predicate; copy all elements from one vector to another excluding even numbers" ) {
        const vector<int>     from{1, 2, 4, 7, 5, 6, 3};
              vector<int>       to;
        const vector<int> expected{1, 7, 5, 3};

        const auto is_even = [](int x) { return x % 2 == 0; };

        remove_copy_if(cbegin(from), cend(from), back_inserter(to), is_even); 

        REQUIRE( expected == to );
    }

}

TEST_CASE( "replace", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "replace all 1s with 0s" ) {
              vector<int>      vec{1, 2, 1, 1, 3, 6, 1};
        const vector<int> expected{0, 2, 0, 0, 3, 6, 0};

        replace(begin(vec), end(vec), 1, 0); 

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "replace_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "replace all even numbers with 1" ) {
              vector<int>      vec{3, 2, 7, 8, 0, 6, 5};
        const vector<int> expected{3, 1, 7, 1, 1, 1, 5};

        const auto is_even = [](int x) { return x % 2 == 0; };

        replace_if(begin(vec), end(vec), is_even, 1); 

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "replace_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements from one vector to another replacing all 1s with 0s" ) {
        const vector<int>     from{1, 2, 1, 1, 3, 6, 1};
              vector<int>       to;
        const vector<int> expected{0, 2, 0, 0, 3, 6, 0};

        replace_copy(
              cbegin(from)
            , cend(from)
            , back_inserter(to)
            , 1
            , 0
        ); 

        REQUIRE( expected == to );
    }

}

TEST_CASE( "replace_copy_if", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "copy all elements from one vector to another replacing all even numbers with 1" ) {
        const vector<int>      from{3, 2, 7, 8, 0, 6, 5};
              vector<int>        to;
        const vector<int>  expected{3, 1, 7, 1, 1, 1, 5};

        const auto is_even = [](int x) { return x % 2 == 0; };

        replace_copy_if(
              cbegin(from)
            , cend(from)
            , back_inserter(to)
            , is_even
            , 1
        ); 

        REQUIRE( expected == to );
    }

}

TEST_CASE( "reverse", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reverse elements in the range" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> expected{5, 4, 3, 2, 1, 0};

        reverse(begin(vec), end(vec));

        REQUIRE( expected == vec );
    }

}

TEST_CASE( "reverse_copy", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reverse elements in the destination range" ) {
        const vector<int>     from{0, 1, 2, 3, 4, 5};
              vector<int>       to;
        const vector<int> expected{5, 4, 3, 2, 1, 0};

        reverse_copy(cbegin(from), cend(from), back_inserter(to));

        REQUIRE( expected == to );
    }

}

TEST_CASE( "rotate", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "rotate first 2 elements to the end" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> expected{2, 3, 4, 5, 0, 1};

        const auto it = rotate(begin(vec), begin(vec) + 2,  end(vec));

        REQUIRE( expected == vec );

        REQUIRE( 0 == *it );
        REQUIRE( cbegin(vec) + 4 == it );

    }

    SECTION( "rotate last 2 elements to the front" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> expected{4, 5, 0, 1, 2, 3};

        const auto it = rotate(begin(vec), begin(vec) + 4,  end(vec));

        REQUIRE( expected == vec );

        REQUIRE( 0 == *it );
        REQUIRE( cbegin(vec) + 2 == it );
    }

    SECTION( "rotate 2nd and 3rd elements with 4th and 5th elements" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> expected{0, 3, 4, 1, 2, 5};

        const auto it = rotate(begin(vec) + 1, begin(vec) + 3,  --end(vec));

        REQUIRE( expected == vec );

        REQUIRE( 1 == *it );
        REQUIRE( cbegin(vec) + 3 == it );
    }
}

TEST_CASE( "shuffle", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "reorder elements in the container based on the provided random function generator" ) {
              vector<int>      vec{0, 1, 2, 3, 4, 5};
        const vector<int> original{0, 1, 2, 3, 4, 5};

        random_device rd;
        mt19937       f(rd());
        // TODO review
        shuffle(begin(vec), end(vec), f);

        REQUIRE( original != vec );
    }

}

TEST_CASE( "swap", "[std] [algorithm] [modifying]" ) {
    
    SECTION( "swaps values" ) {
        int          x = 1;
        int          y = 2;

        swap(x, y);

        REQUIRE( 2 == x );
        REQUIRE( 1 == y );
    }

    SECTION( "use swap to set the object to a default constructed state" ) {
        vector<int>          vec{0, 1, 2};
        vector<int> empty_vector;
    
        swap(vec,  empty_vector);
        
        REQUIRE (vec.empty() ); 

    }

}

