#include <catch.hpp>
#include <vector>
#include <string>

using namespace std;

static int static_i = 0;

TEST_CASE( "for (auto v : r)", "[std] [modern] [range loop]" ) {
    
    SECTION( "access each element by value" ) {
              vector<int>          vec{0, 1, 2, 3, 4};
        const vector<int> expected_vec{0, 1, 2, 3, 4};
              vector<int>           to; 
        const vector<int>  expected_to{0, 2, 4, 6, 8};

        for (auto v : vec) {
            v *= 2;
            to.push_back(v);
        }

        REQUIRE( expected_vec == vec );
        REQUIRE( expected_to  == to );
    }

}

TEST_CASE( "(const auto& v : r)", "[std] [modern] [range loop]" ) {
    
    SECTION( "access each element by const reference" ) {
              vector<int>          vec{0, 1, 2, 3, 4};
              vector<int>           to; 
        const vector<int>  expected_to{0, 1, 2, 3, 4};

        for (const auto& v : vec) {
            to.push_back(v);
        }

        REQUIRE( expected_to  == to );
    }

}

TEST_CASE( "(auto& v : r)", "[std] [modern] [range loop]" ) {

    SECTION( "access each element by reference" ) {
              vector<int>       vec{0, 1, 2, 3, 4};
        const vector<int>  expected{0, 2, 4, 6, 8};

        for (auto& v : vec) {
            v *= 2; 
        }

        REQUIRE( expected == vec );
    }

}
