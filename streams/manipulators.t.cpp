#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "boolalpha", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "<< boolalpha" ) {
        ostringstream sout;

        sout << boolalpha << true << ' ' << false;

        REQUIRE( "true false" == sout.str() );
    }

    SECTION( ">> boolalpha" ) {
        istringstream sin{"true false"};

        bool value = false;

        sin >> boolalpha >> value ;
        REQUIRE( true ==  value);

        sin >> value ;
        REQUIRE( false ==  value);
    }

    SECTION( "invalid >> boolalpha" ) {
        istringstream sin{"1 0"};

        bool value = false;
        sin >> boolalpha >> value ;

        REQUIRE_FALSE( sin );
    }

}

TEST_CASE( "noboolalpha", "[std] [ostream] [manipulators]" ) {

    SECTION( "<< noboolalpha" ) {
        ostringstream sout;

        sout << noboolalpha << true << ' ' << false;

        REQUIRE( "1 0" == sout.str() );
    }

    SECTION( ">> noboolalpha" ) {
        istringstream sin{"1 0"};

        bool value = false;

        sin >> noboolalpha >> value ;
        REQUIRE( true ==  value);

        sin >> value ;
        REQUIRE( false ==  value);
    }

    SECTION( "invalid >> noboolalpha" ) {
        istringstream sin{"true false"};

        bool value = false;
        sin >> noboolalpha >> value ;

        REQUIRE_FALSE( sin );
    }

}

TEST_CASE( "showbase", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "<< showbase << hex" ) {
        ostringstream sout;

        sout << showbase << hex << 255;

        REQUIRE( "0xff" == sout.str() );
    }

    SECTION( "<< showbase << oct" ) {
        ostringstream sout;

        sout << showbase << oct << 511;

        REQUIRE( "0777" == sout.str() );
    }

    SECTION( "<< showbase << put_money" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << showbase << put_money(cents);

        REQUIRE( "$1.99" == sout.str() );
    }

    SECTION( ">> showbase >> get_money" ) {
        istringstream sin{"$1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> showbase >> get_money(cents);

        REQUIRE( 199.0 == cents );
    }

    SECTION( "invalid >> showbase >> get_money" ) {
        istringstream sin{"1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> showbase >> get_money(cents);
        
        REQUIRE_FALSE( sin );
    }

}

TEST_CASE( "noshowbase", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "<< noshowbase << hex" ) {
        ostringstream sout;

        sout << noshowbase << hex << 255;

        REQUIRE( "ff" == sout.str() );
    }

    SECTION( "<< noshowbase << oct" ) {
        ostringstream sout;

        sout << noshowbase << oct << 511;

        REQUIRE( "777" == sout.str() );
    }

    SECTION( "<< noshowbase << put_money" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << noshowbase << put_money(cents);

        REQUIRE( "1.99" == sout.str() );
    }

    SECTION( ">> noshowbase >> get_money" ) {
        istringstream sin{"1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> noshowbase >> get_money(cents);

        REQUIRE( 199.0 == cents );
    }

    SECTION( "has base >> noshowbase >> get_money" ) {
        istringstream sin{"$1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> noshowbase >> get_money(cents);
        
        REQUIRE( 199.0 == cents );
    }

}

TEST_CASE( "showpoint noshowpoint", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "floating-point with zeroes after decimal point" ) {
        stringstream ss;

        ss << showpoint << 27.0 << " " << noshowpoint << 27.0;

        REQUIRE( "27.0000 27" == ss.str() );
    }

    SECTION( "floating-point with non zeroes after decimal point" ) {
        stringstream ss;

        ss << showpoint << 27.12 << " " << noshowpoint << 27.12;

        REQUIRE( "27.1200 27.12" == ss.str() );
    }

}
