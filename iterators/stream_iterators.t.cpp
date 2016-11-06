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
   
}

