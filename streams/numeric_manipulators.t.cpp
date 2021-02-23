#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "boolalpha", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< boolalpha" ) {
        ostringstream sout;

        sout << boolalpha << true << ' ' << false;

        REQUIRE( sout.str() == "true false" );
    }

    SECTION( ">> boolalpha" ) {
        istringstream sin{"true false"};

        bool value = false;

        sin >> boolalpha >> value ;
        REQUIRE( value );

        sin >> value ;
        REQUIRE_FALSE( value );
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

        sout << noboolalpha << true << "  " << false;

        REQUIRE( sout.str() == "1  0" );
    }

    SECTION( ">> noboolalpha" ) {
        istringstream sin{"1 0"};

        bool value = false;

        sin >> noboolalpha >> value ;
        REQUIRE( value );

        sin >> value ;
        REQUIRE_FALSE( value );
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

        REQUIRE( sout.str() == "0xff" );
    }

    SECTION( "<< showbase << oct" ) {
        ostringstream sout;

        sout << showbase << oct << 511;

        REQUIRE(  sout.str() == "0777" );
    }

    SECTION( "<< showbase << put_money" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << showbase << put_money(cents);

        REQUIRE( sout.str() == "$1.99" );
    }

    SECTION( ">> showbase >> get_money" ) {
        istringstream sin{"$1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> showbase >> get_money(cents);

        REQUIRE(  cents == 199.0 );
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

        REQUIRE( sout.str() == "ff" );
    }

    SECTION( "<< noshowbase << oct" ) {
        ostringstream sout;

        sout << noshowbase << oct << 511;

        REQUIRE( sout.str() == "777" );
    }

    SECTION( "<< noshowbase << put_money" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << noshowbase << put_money(cents);

        REQUIRE( sout.str() == "1.99" );
    }

    SECTION( ">> noshowbase >> get_money" ) {
        istringstream sin{"1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> noshowbase >> get_money(cents);

        REQUIRE( cents == 199.0 );
    }

    SECTION( "has base >> noshowbase >> get_money" ) {
        istringstream sin{"$1.99"};
        sin.imbue(locale("en_US"));

        long double cents = 0;
        sin >> noshowbase >> get_money(cents);
        
        REQUIRE( cents == 199.0 );
    }

}

TEST_CASE( "showpos", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< showpos << integer" ) {
        ostringstream sout;

        sout << showpos << 27 ;

        REQUIRE( sout.str() == "+27" );
    }

    SECTION( "<< showpos << floating-point" ) {
        ostringstream sout;

        sout << showpos << 27.123 ;

        REQUIRE( sout.str() == "+27.123" );
    }

}

TEST_CASE( "noshowpos", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< noshowpos << integer" ) {
        ostringstream sout;

        sout << noshowpos << 27 ;

        REQUIRE( sout.str() == "27" );
    }

    SECTION( "<< noshowpos << floating-point" ) {
        ostringstream sout;

        sout << noshowpos << 27.123 ;

        REQUIRE( sout.str() == "27.123" );
    }

}

TEST_CASE( "uppercase", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< uppercase << hex << integer" ) {
        ostringstream sout;;
        
        sout << uppercase << hex << 255;

        REQUIRE( sout.str() == "FF" );
    }

    SECTION( "<< uppercase << hex << floating-point" ) {
        ostringstream sout;;
        
        sout << uppercase << hex << 1e-35;

        REQUIRE( sout.str() == "1E-35" );
    }

}

TEST_CASE( "nouppercase", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< nouppercase << hex << integer" ) {
        ostringstream sout;;
        
        sout << nouppercase << hex << 255;

        REQUIRE( sout.str() == "ff" );
    }

    SECTION( "<< uppercase << hex << floating-point" ) {
        ostringstream sout;;
        
        sout << nouppercase << hex << 1e-35;

        REQUIRE( sout.str() == "1e-35" );
    }

}

TEST_CASE( "hex", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in hexadecimal format" ) {
        ostringstream sout;

        sout << hex << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "f ff 1ff" ); 
    }

    SECTION( "output number in hexadecimal format with uppercase base prefix" ) {
        ostringstream sout;

        sout << hex << showbase << uppercase << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "0XF 0XFF 0X1FF" ); 
    }

    SECTION( "parse number from input in hex format" ) {
        istringstream sin{"10 10"};
        
        int i{};

        sin >> i;
        REQUIRE( i == 10 ); 

        sin >> hex >> i;
        REQUIRE( i == 16 ); 
    }

}

TEST_CASE( "oct", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in octal format" ) {
        ostringstream sout;

        sout << oct << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "17 377 777" ); 
    }

    SECTION( "output number in octal format with base prefix" ) {
        ostringstream sout;

        sout << oct << showbase << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "017 0377 0777" ); 
    }

    SECTION( "parse number from input in octal format" ) {
        istringstream sin{"10 10"};
        
        int i{};

        sin >> i;
        REQUIRE( i == 10 ); 

        sin >> oct >> i;
        REQUIRE( i == 8 ); 
    }

}

TEST_CASE( "dec", "[std] [streams] [manipulators]" ) {
    
    SECTION( "output number in decimal format" ) {
        ostringstream sout;

        sout << dec << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "15 255 511" ); 
    }

    SECTION( "by default output number in decimal format" ) {
        ostringstream sout;

        sout << 15 << ' ' << 0xFF << ' ' << 0777;
        
        REQUIRE( sout.str() == "15 255 511" ); 
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
        
        REQUIRE( sout.str() == "20 16 10 16" ); 
    }

    SECTION( ">> set numeric base" ) {
        istringstream sin{"20 16 10 16"};;

        int invalid_base_will_default_to_base_10 = 17;
        int i{}; 

        sin >> setbase(8) >> i;
        REQUIRE( i == 16 );

        sin >> setbase(10) >> i;
        REQUIRE( i == 16 );

        sin >> setbase(16) >> i;
        REQUIRE( i == 16 );

        sin >> setbase(invalid_base_will_default_to_base_10) >> i;
        REQUIRE( i == 16 );
    }

}
