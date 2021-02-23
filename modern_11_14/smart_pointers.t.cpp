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
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "check if stored  pointer is null" ) {
        unique_ptr<resource>  ptr;
        REQUIRE_FALSE( ptr );
        
        ptr.reset(new resource);
        REQUIRE( ptr );
    }

    SECTION( "use * and ->  operators to access members of the owned pointer object" ) {
        unique_ptr<resource> ptr = make_unique<resource>(1);
        REQUIRE( ptr );
        REQUIRE( (*ptr).i == 1 );
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
            REQUIRE( ptr2->i == 2 );

            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1);
    }

    SECTION( "move assign" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_unique<resource>(3);

            decltype(ptr1) ptr2;

            ptr2 = move(ptr1);
            REQUIRE( ptr2 );
            REQUIRE( ptr2->i == 3 );

            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "get" ) {
        resource::dtor_called = 0; 
        {
            auto ptr = make_unique<resource>(4);

            resource* raw_ptr = ptr.get();
            REQUIRE( raw_ptr->i  == 4 );
            REQUIRE( ptr );
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "release" ) {
        resource::dtor_called = 0; 
        resource* raw_ptr = nullptr;
        {
            auto ptr = make_unique<resource>(5);

            raw_ptr = ptr.release();
            REQUIRE( raw_ptr->i == 5 );
            REQUIRE_FALSE( ptr );
        }
        REQUIRE( resource::dtor_called == 0 );

        delete raw_ptr;
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "reset" ) {
        resource::dtor_called = 0; 

        unique_ptr<resource>  ptr;

        ptr.reset(new resource(6));

        REQUIRE( ptr );
        REQUIRE( resource::dtor_called  == 0 );
        REQUIRE( ptr->i == 6 );

        ptr.reset(new resource(7));

        REQUIRE( ptr );
        REQUIRE( resource::dtor_called == 1);
        REQUIRE( ptr->i == 7 );

        ptr.reset();

        REQUIRE_FALSE( ptr );
        REQUIRE( resource::dtor_called == 2 );
    }

    SECTION( "pass to function by value" ) {
        resource::dtor_called = 0; 

        auto pass_to_function_by_value = [](unique_ptr<resource> p) {};
        auto ptr = make_unique<resource>(8);

        pass_to_function_by_value(move(ptr)); 

        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "==" ) {
        auto ptr1 = make_unique<int>(9);
        auto ptr2 = make_unique<int>(9);

        REQUIRE_FALSE( ptr1 == ptr2);

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

        REQUIRE( delete_count == 1 );
    }

}

TEST_CASE( "shared_ptr", "[std] [modern] [smart pointers]" ) {

    SECTION( "automatically reclame resource using shared_ptr" ) {
        {
            shared_ptr<resource>  ptr1(new resource);
            resource::dtor_called = 0; 
            {
                shared_ptr<resource>  ptr2(ptr1);
            }
            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "check if stored pointer is null" ) {
        shared_ptr<resource>  ptr;
        REQUIRE_FALSE( ptr );
        
        ptr.reset(new resource);
        REQUIRE( ptr );
    }

    SECTION( "use_count" ) {
        shared_ptr<resource>  ptr1;
        REQUIRE( ptr1.use_count() == 0 );

        ptr1.reset(new resource);
        REQUIRE( ptr1.use_count() == 1 );

        auto ptr2 = ptr1;;
        REQUIRE( ptr1.use_count() == 2 );
        REQUIRE( ptr2.use_count() == 2);
    }

    SECTION( "use * and ->  operators to access members of the owned pointer object" ) {
        shared_ptr<resource> ptr = make_shared<resource>(1);
        REQUIRE( ptr );
        REQUIRE( ptr->i == 1 );
    }

    SECTION( "copy" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_shared<resource>(2);

            auto ptr2(ptr1);
            REQUIRE( ptr1 );
            REQUIRE( ptr2 );
            REQUIRE( ptr2->i == 2 );

            REQUIRE( resource::dtor_called == 0);
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "assign" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_shared<resource>(3);

            decltype(ptr1) ptr2;

            ptr2 = ptr1;
            REQUIRE( ptr1 );
            REQUIRE( ptr2 );
            REQUIRE( ptr2->i == 3 );

            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1);
    }

    SECTION( "move copy" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_shared<resource>(2);

            auto ptr2(move(ptr1));
            REQUIRE( ptr2 );
            REQUIRE( ptr2->i == 2);
            REQUIRE( ptr2.unique() );
            REQUIRE( ptr2.use_count() == 1 );

            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "move assign" ) {
        resource::dtor_called = 0; 
        {
            auto ptr1 = make_shared<resource>(3);

            decltype(ptr1) ptr2;

            ptr2 = move(ptr1);
            REQUIRE( ptr2 );
            REQUIRE( ptr2->i == 3 );
            REQUIRE( ptr2.unique() );
            REQUIRE( ptr2.use_count() == 1 );

            REQUIRE( resource::dtor_called == 0 );
        }
        REQUIRE( resource::dtor_called == 1 );
    }

    SECTION( "get" ) {
        resource::dtor_called = 0; 
        {
            auto ptr = make_shared<resource>(4);

            resource* raw_ptr = ptr.get();
            REQUIRE( raw_ptr->i == 4 );
            REQUIRE( ptr );
        }
        REQUIRE( 1 == resource::dtor_called );
    }

    SECTION( "reset" ) {
        resource::dtor_called = 0; 

        shared_ptr<resource>  ptr1;

        ptr1.reset(new resource(6));

        REQUIRE( ptr1 );
        REQUIRE( resource::dtor_called == 0 );
        REQUIRE( ptr1->i == 6 );

        ptr1.reset(new resource(7));

        REQUIRE( ptr1 );
        REQUIRE( resource::dtor_called == 1 );
        REQUIRE( ptr1->i == 7 );

        auto ptr2 = ptr1;
        ptr1.reset();

        REQUIRE( resource::dtor_called == 1 );
        REQUIRE_FALSE( ptr1 );

        ptr2.reset();

        REQUIRE_FALSE( ptr2 );
        REQUIRE( resource::dtor_called == 2 );
    }

    SECTION( "pass to function by value" ) {
        resource::dtor_called = 0; 

        auto pass_to_function_by_value = [](shared_ptr<resource> p) {};
        auto ptr = make_shared<resource>(8);

        pass_to_function_by_value(ptr); 

        REQUIRE( resource::dtor_called == 0 );
    }

    SECTION( "==" ) {
        auto ptr1 = make_shared<int>(9);
        auto ptr2 = make_shared<int>(9);

        REQUIRE_FALSE( ptr1 == ptr2);

        ptr1.reset();
        REQUIRE( ptr1 == nullptr);

        ptr1 = ptr2;
        REQUIRE( ptr1 == ptr2);
    }

    SECTION( "custom deleter" ) {
        int delete_count = 0;
        auto deleter = [&delete_count] (auto value) { delete value; ++delete_count; };
        
        {
            shared_ptr<int> ptr(new int(10), deleter);; 
        }

        REQUIRE( delete_count == 1 );
    }

    SECTION( "pointer_cast" ) {
        struct base {
            virtual void foo() = 0;
            virtual ~base() {}
        };

        struct derived1 : public base {
            virtual void foo() override {}
            void derived1_only() {};
        };

        struct derived2 : public base {
            virtual void foo() override {}
            void derived2_only() {};
        };

        shared_ptr<base> ptr_base = make_shared<derived1>(); 
         
        // const_pointer_cast
        shared_ptr<const base> const_ptr = ptr_base; 
        ptr_base = const_pointer_cast<base>(const_ptr);

        // dynamic_pointer_cast safe and correct
        auto ptr_derived1 = dynamic_pointer_cast<derived1>(ptr_base);
        REQUIRE( ptr_derived1 );

        // static_pointer_cast not safe and correct
        ptr_derived1 = static_pointer_cast<derived1>(ptr_base);
        REQUIRE( ptr_derived1 );

        // dynamic_pointer_cast safe and incorrect
        auto ptr_derived2 = dynamic_pointer_cast<derived2>(ptr_derived1);
        REQUIRE_FALSE( ptr_derived2 );
        
        // static_pointer_cast undefined 
        ptr_derived2 = static_pointer_cast<derived2>(ptr_base);
        REQUIRE( ptr_derived2 );
    }

}

TEST_CASE( "weak_ptr", "[std] [modern] [smart pointers]" ) {
    
    SECTION( "basic usage assing/lock" ) {
        resource::dtor_called = 0;
        shared_ptr<resource> shared = make_shared<resource>();

        weak_ptr<resource> weak = shared;
        REQUIRE_FALSE( weak.expired() );

        {
            shared_ptr<resource> ptr = weak.lock();
            REQUIRE( ptr );
        }
        
        shared.reset();
        REQUIRE( resource::dtor_called == 1 );
        REQUIRE( weak.expired() );

        {
            shared_ptr<resource> ptr = weak.lock();
            REQUIRE_FALSE( ptr );
        }
    }

    SECTION( "reset" ) {
        shared_ptr<resource> shared = make_shared<resource>();

        weak_ptr<resource> weak(shared);
        REQUIRE_FALSE( weak.expired() );

        weak.reset();
        REQUIRE( weak.expired() );
        REQUIRE( weak.use_count() == 0 );
    }

    SECTION( "use_count" ) {
        auto shared1 = make_shared<resource>();

        weak_ptr<resource> weak = shared1;
        REQUIRE( weak.use_count() == 1 );

        auto shared2 = shared1;
        REQUIRE( weak.use_count() == 2 );

        auto shared3 = shared1;
        REQUIRE( weak.use_count() == 3 );
    }

}
