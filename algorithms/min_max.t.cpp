#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

TEST_CASE( "clamp(C++17)", "[std] [algorithm] [min max]" ) {
    
    SECTION( "returns value, low or high depending on the comparison" ) {
        const int low   = 1;
        const int high  = 128;
        bool undefined_behaviour = !(low < high);
        REQUIRE_FALSE( undefined_behaviour ); 

        int value_less_than_low = low - 1;
        REQUIRE( clamp(value_less_than_low, low, high) == low );

        int value_greter_than_high = high + 1;
        REQUIRE( clamp(value_greter_than_high, low, high) == high );

        int value = low;
        REQUIRE( clamp(value, low, high) == value );
        value = (low + high) / 2;
        REQUIRE( clamp(value, low, high) == value );
        value = high;
        REQUIRE( clamp(value, low, high) == value );
    } 

}

TEST_CASE( "max", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return max value" ) {
        const int x = 0;
        const int y = 1;

        const int max_value = max(x, y);

        REQUIRE( max_value == 1);
    } 

    SECTION( "return max absolute value" ) {
        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const int abs_max_value = max(-10, 5, compare_abs);

        REQUIRE( abs_max_value == -10 );
    } 

    SECTION( "return max value as constexpr" ) {
        constexpr int max_value = max(0, 1);

        static_assert(max_value == 1, "max_value should be 1");
    }

    SECTION( "return max value in the initializer list" ) {
        const auto init_list = {1, 9, 3,   17}; 

        const int max_value = max(init_list);

        REQUIRE( max_value == 17 );
    }

    SECTION( "return max absolute value in the initializer list" ) {
        const auto init_list = {-100,   1, -9, 3, 17}; 

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const int abs_max_value = max(init_list, compare_abs);

        REQUIRE( abs_max_value == -100 );
    }
}

TEST_CASE( "max_element", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return max element in the range" ) {
        const vector<int> vec{1, 9, 2,   10};

        const auto max_it = max_element(cbegin(vec), cend(vec));

        REQUIRE( *max_it == 10 );
    } 

    SECTION( "return absolute max element in the range" ) {
        const vector<int> vec{1,   -15,   9, 2, 10};

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const auto abs_max_it = max_element(cbegin(vec), cend(vec), compare_abs);

        REQUIRE( *abs_max_it == -15 );
    }

}

TEST_CASE( "min", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return min value" ) {
        const int x = 0;
        const int y = 1;

        const int min_value = min(x, y);

        REQUIRE( min_value == 0 );
    } 

    SECTION( "return min absolute value" ) {
        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const int abs_min_value = min(-10, 5, compare_abs);

        REQUIRE( abs_min_value == 5 );
    } 

    SECTION( "return min value as constexpr" ) {
        constexpr int min_value = min(0, 1);

        static_assert( min_value == 0, "min_value should be 1");
    }

    SECTION( "return min value in the initializer list" ) {
        const auto init_list = {1,   9, 3, 17}; 

        const int min_value = min(init_list);

        REQUIRE( min_value == 1 );
    }

    SECTION( "return min absolute value in the initializer list" ) {
        const auto init_list = {-100,   1,   -9, 3, 17}; 

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const int abs_min_value = min(init_list, compare_abs);

        REQUIRE( abs_min_value == 1);
    }

}

TEST_CASE( "min_element", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return min element in the range" ) {
        const vector<int> vec{5, 9,   2,   10};

        const auto min_it = min_element(cbegin(vec), cend(vec));

        REQUIRE( *min_it == 2 );
    } 

    SECTION( "return absolute min element in the range" ) {
        const vector<int> vec{1,   -15, 9, 2, 10};

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const auto abs_min_it = min_element(cbegin(vec), cend(vec), compare_abs);

        REQUIRE( *abs_min_it == 1 );
    }

}

TEST_CASE( "minmax(C++11)", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return minmax values" ) {
        int x = 0;
        int y = 1;

        const auto min_max = minmax(x, y);

        REQUIRE( min_max.first  == 0 );
        REQUIRE( min_max.second == 1);
    } 

    SECTION( "return minmax absolute values" ) {
        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const pair<int, int> abs_min_max = minmax(-10, 5, compare_abs);

        CHECK( abs_min_max.first  == 5 );
        CHECK( abs_min_max.second == -10 );
    }

    SECTION( "return minmax values as constexpr" ) {
        constexpr pair<int, int> min_max = minmax(0, 1);
        
        static_assert(min_max.first  == 0,  "min should be 0");
        static_assert(min_max.second == 1, "max should be 1");
    }

    SECTION( "return min value in the initializer list" ) {
        const auto init_list = {1, 9, 3, 17}; 

        const auto min_max = minmax(init_list);

        REQUIRE( min_max.first  == 1);
        REQUIRE( min_max.second == 17);
    }

    SECTION( "return minmax absolute values in the initializer list" ) {
        const auto init_list = {-100, 1, -9, 3, 17}; 

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const auto abs_min_max = minmax(init_list, compare_abs);

        REQUIRE( abs_min_max.first  == 1 );
        REQUIRE( abs_min_max.second == -100 );
    }

}

TEST_CASE( "minmax_element(C++11)", "[std] [algorithm] [min max]" ) {
    
    SECTION( "return minmax elements in the range" ) {
        const vector<int> vec{5, 9, 2, 10};

        const auto min_max_it = minmax_element(cbegin(vec), cend(vec));

        REQUIRE( *min_max_it.first  == 2 );
        REQUIRE( *min_max_it.second == 10);
    } 

    SECTION( "return absolute min element in the range" ) {
        const vector<int> vec{1, -15, 9, 2, 10};

        auto compare_abs = [](int x, int y) { return abs(x) < abs(y); };

        const auto abs_min_max_it = minmax_element(cbegin(vec), cend(vec), compare_abs);

        REQUIRE( *abs_min_max_it.first  == 1 );
        REQUIRE( *abs_min_max_it.second == -15 );
    }

}
