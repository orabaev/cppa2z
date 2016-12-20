#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "boolalpha", "[std] [streams] [manipulators]" ) {
    
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

TEST_CASE( "noboolalpha", "[std] [streams] [manipulators]" ) {

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

TEST_CASE( "showbase", "[std] [streams] [manipulators]" ) {
    
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

TEST_CASE( "noshowbase", "[std] [streams] [manipulators]" ) {
    
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

TEST_CASE( "showpos", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< showpos << integer" ) {
        ostringstream sout;

        sout << showpos << 27 ;

        REQUIRE( "+27" == sout.str() );
    }

    SECTION( "<< showpos << floating-point" ) {
        ostringstream sout;

        sout << showpos << 27.123 ;

        REQUIRE( "+27.123" == sout.str() );
    }

}

TEST_CASE( "noshowpos", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< noshowpos << integer" ) {
        ostringstream sout;

        sout << noshowpos << 27 ;

        REQUIRE( "27" == sout.str() );
    }

    SECTION( "<< noshowpos << floating-point" ) {
        ostringstream sout;

        sout << noshowpos << 27.123 ;

        REQUIRE( "27.123" == sout.str() );
    }

}

TEST_CASE( "uppercase", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< uppercase << hex << integer" ) {
        ostringstream sout;;
        
        sout << uppercase << hex << 255;

        REQUIRE( "FF" == sout.str() );
    }

    SECTION( "<< uppercase << hex << floating-point" ) {
        ostringstream sout;;
        
        sout << uppercase << hex << 1e-35;

        REQUIRE( "1E-35" == sout.str() );
    }

}

TEST_CASE( "nouppercase", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< nouppercase << hex << integer" ) {
        ostringstream sout;;
        
        sout << nouppercase << hex << 255;

        REQUIRE( "ff" == sout.str() );
    }

    SECTION( "<< uppercase << hex << floating-point" ) {
        ostringstream sout;;
        
        sout << nouppercase << hex << 1e-35;

        REQUIRE( "1e-35" == sout.str() );
    }

}

TEST_CASE( "hex", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in hexadecimal format" ) {
        ostringstream sout;

        sout << hex << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "f ff 1ff" == sout.str() ); 
    }

    SECTION( "output number in hexadecimal format with uppercase base prefix" ) {
        ostringstream sout;

        sout << hex << showbase << uppercase << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "0XF 0XFF 0X1FF" == sout.str() ); 
    }

    SECTION( "parse number from input in hex format" ) {
        istringstream sin{"10 10"};
        
        int i{};

        sin >> i;
        REQUIRE( 10 == i ); 

        sin >> hex >> i;
        REQUIRE( 16 == i ); 
    }

}

TEST_CASE( "oct", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in octal format" ) {
        ostringstream sout;

        sout << oct << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "17 377 777" == sout.str() ); 
    }

    SECTION( "output number in octal format with base prefix" ) {
        ostringstream sout;

        sout << oct << showbase << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "017 0377 0777" == sout.str() ); 
    }

    SECTION( "parse number from input in octal format" ) {
        istringstream sin{"10 10"};
        
        int i{};

        sin >> i;
        REQUIRE( 10 == i ); 

        sin >> oct >> i;
        REQUIRE( 8 == i ); 
    }

}

TEST_CASE( "dec", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in decimal format" ) {
        ostringstream sout;

        sout << dec << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "15 255 511" == sout.str() ); 
    }

    SECTION( "by default output number in decimal format" ) {
        ostringstream sout;

        sout << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( "15 255 511" == sout.str() ); 
    }

}

TEST_CASE( "setbase", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< set numeric base" ) {
        ostringstream sout;

        int invalid_base_will_default_to_base_10 = 17;

        sout << setbase(8) << 16
             << ' '
             << setbase(10)  << 16
             << ' '
             << setbase(16)  << 16
             << ' '
             << setbase(invalid_base_will_default_to_base_10)  << 16;
        
        REQUIRE( "20 16 10 16" == sout.str() ); 
    }

    SECTION( ">> set numeric base" ) {
        istringstream sin{"20 16 10 16"};;

        int invalid_base_will_default_to_base_10 = 17;
        int i{}; 

        sin >> setbase(8) >> i;
        REQUIRE( 16 == i );

        sin >> setbase(10) >> i;
        REQUIRE( 16 == i );

        sin >> setbase(16) >> i;
        REQUIRE( 16 == i );

        sin >> setbase(invalid_base_will_default_to_base_10) >> i;
        REQUIRE( 16 == i );
    }

}
