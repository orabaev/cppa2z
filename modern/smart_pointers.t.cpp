#include <catch.hpp>
#include <memory>
#include <type_traits>
#include <functional>

using namespace std;

TEST_CASE( "nullptr", "[std] [modern] [smart pointers]" ) {
    
    SECTION( "use nullptr istead of NULL" ) {
        int* ptr = new int(10);

        REQUIRE( ptr );

        delete ptr;
        ptr = nullptr;

        REQUIRE_FALSE( ptr );
    }

    SECTION( "properly resolve overload by passing nullptr" ) {
        struct nullptr_int_overload {
            static bool is_pointer_argument(void* ) { return true; }
            static bool is_pointer_argument(int   ) { return false; }
        };

        REQUIRE( nullptr_int_overload::is_pointer_argument(nullptr) );

        REQUIRE_FALSE( nullptr_int_overload::is_pointer_argument(10) );
    }

}

// define resource class used in smart pointer tests
namespace {
struct resource {
    int i = 0;
    static int dtor_called;
    resource() {}
    resource(int x): i(x) {}; 
    ~resource() { ++dtor_called; };
};
int resource::dtor_called = 0; 
}


TEST_CASE( "unique_ptr", "[std] [modern] [smart pointers]" ) {

    SECTION( "automatically reclame resource using unique_ptr" ) {
        resource::dtor_called = 0; 
        {
            unique_ptr<resource>  ptr(new resource);
        }
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "use * and ->  operators to access members of the owned pointer object" ) {
        unique_ptr<resource> ptr = make_unique<resource>(1);
        REQUIRE( ptr );
        REQUIRE( 1 == (*ptr).i );
    }

    SECTION( "cannot copy or assign" ) {
        static_assert( is_copy_constructible<unique_ptr<int>>::value == 0    , "cannot copy" );
        static_assert( is_copy_assignable<unique_ptr<int>>::value    == 0    , "cannot assing" );
    }

    SECTION( "move copy" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_unique<resource>(2);

            auto ptr2(move(ptr1));
            REQUIRE( ptr2 );
            REQUIRE( 2 == ptr2->i );

            REQUIRE( 0 == resource::dtor_called );
        }
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "move assign" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_unique<resource>(3);

            decltype(ptr1) ptr2;

            ptr2 = move(ptr1);
            REQUIRE( ptr2 );
            REQUIRE( 3 == ptr2->i );

            REQUIRE( 0 == resource::dtor_called );
        }
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "get" ) {
        resource::dtor_called = 0; 
        {
            auto ptr = make_unique<resource>(4);

            resource* raw_ptr = ptr.get();
            REQUIRE( 4 == raw_ptr->i );
            REQUIRE( ptr );
        }
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "release" ) {
        resource::dtor_called = 0; 
        resource* raw_ptr = nullptr;
        {
            auto ptr = make_unique<resource>(5);

            raw_ptr = ptr.release();
            REQUIRE( 5 == raw_ptr->i );
            REQUIRE_FALSE( ptr );
        }
        REQUIRE( 0 == resource::dtor_called );

        delete raw_ptr;
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "reset" ) {
        resource::dtor_called = 0; 

        unique_ptr<resource>  ptr;

        ptr.reset(new resource(6));

        REQUIRE( ptr );
        REQUIRE( 0 == resource::dtor_called );
        REQUIRE( 6 == ptr->i );

        ptr.reset(new resource(7));

        REQUIRE( ptr );
        REQUIRE( 1 == resource::dtor_called );
        REQUIRE( 7 == ptr->i );

        ptr.reset();

        REQUIRE_FALSE( ptr );
        REQUIRE( 2 == resource::dtor_called );
    }

    SECTION( "pass to function by value" ) {
        resource::dtor_called = 0; 

        auto pass_to_function_by_value = [](unique_ptr<resource> p) {};
        auto ptr = make_unique<resource>(8);

        pass_to_function_by_value(move(ptr)); 

        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "compares value owned pointers" ) {
        auto ptr1 = make_unique<int>(9);
        auto ptr2 = make_unique<int>(9);

        REQUIRE( ptr1 != ptr2);

        ptr1.reset();
        REQUIRE( ptr1 == nullptr);
    }

    SECTION( "custom deleter" ) {
        using unique_ptr_d = std::unique_ptr<int, std::function<void(int*)>>;

        int delete_count = 0;
        auto deleter = [&delete_count] (auto value) { delete value; ++delete_count; };
        
        {
            unique_ptr_d ptr(new int(10), deleter);; 
        }

        REQUIRE( 1 == delete_count );
    }

}
