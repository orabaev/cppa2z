#include <catch.hpp>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include <list>

using namespace std;

TEST_CASE( "output iterator", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "ostream_iterator" ) {
        const vector<int> vec{1, 2, 3, 4, 5};
        const string expected{"1->2->3->4->5->"};

        ostringstream sout; 
        const string  delimiter{"->"};

        auto output_it = ostream_iterator<int>(sout, "->"); 
        
        copy(cbegin(vec), cend(vec), output_it);

        REQUIRE( expected == sout.str() );
    } 
 
    SECTION( "insert_iterator" ) {
        const vector<int>     from{1, 2, 3, 4, 5};
              set<int>          to;
        const set<int>    expected{1, 2, 3, 4, 5};

        auto output_it = inserter(to, end(to));

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    } 

    SECTION( "back_insert_iterator" ) {
        const vector<int>     from{1, 2, 3, 4, 5};
              list<int>         to;
        const list<int>   expected{1, 2, 3, 4, 5};

        auto output_it = back_inserter(to);

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }

    SECTION( "front_insert_iterator" ) {
        const vector<int>     from{1, 2, 3, 4, 5};
              list<int>         to;
        const list<int>   expected{5, 4, 3, 2, 1};

        auto output_it = front_inserter(to);

        copy(cbegin(from), cend(from), output_it);

        REQUIRE( expected == to );
    }
    
}

