#include <catch.hpp>
#include <sstream>
#include <fstream>

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

TEST_CASE( "showpoint", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< showpoint << floating-point with zeroes after decimal point" ) {
        ostringstream sout;

        sout << showpoint << 27.0 ;

        REQUIRE( "27.0000" == sout.str() );
    }

    SECTION( "<< showpoint << floating-point with no zeroes after decimal point" ) {
        ostringstream sout;

        sout << showpoint << 27.12 ;

        REQUIRE( "27.1200" == sout.str() );
    }

}

TEST_CASE( "noshowpoint", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< noshowpoint << floating-point with zeroes after decimal point" ) {
        ostringstream sout;

        sout << noshowpoint << 27.0 ;

        REQUIRE( "27" == sout.str() );
    }

    SECTION( "<< noshowpoint << floating-point with non zeroes after decimal point" ) {
        ostringstream sout;

        sout << noshowpoint << 27.12 ;

        REQUIRE( "27.12" == sout.str() );
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

TEST_CASE( "skipws", "[std] [streams] [manipulators]" ) {
    
    SECTION( ">> skipws >> character" ) {
        istringstream sin{"A B C"};
        
        char a, b, c = '\0';        

        sin >> skipws >> a >> b >> c;

        REQUIRE( 'A' == a);
        REQUIRE( 'B' == b );
        REQUIRE( 'C' == c );
    }

}

TEST_CASE( "noskipws", "[std] [streams] [manipulators]" ) {
    
    SECTION( ">> skipws >> character" ) {
        istringstream sin{"A B C"};
        
        char a, b, c = '\0';        

        sin >> noskipws >> a >> b >> c;

        REQUIRE( 'A' == a);
        REQUIRE( ' ' == b );
        REQUIRE( 'B' == c );
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

TEST_CASE( "unitbuf", "[std] [streams] [manipulators]" ) {
    
    SECTION( "automatically flushes the buffer after each output operation" ) {
        ofstream fout("unitbuf.tmp");;
        fout << unitbuf << "flushed";
        
        ifstream fin("unitbuf.tmp");;
        string str;
        fin >> str; 

        REQUIRE( "flushed" == str );
        
        fout.close();
        fin.close();
        remove("unitbuf.tmp");
    }

}

TEST_CASE( "nounitbuf", "[std] [streams] [manipulators]" ) {
    
    SECTION( "does not automatically flush the buffer after each output operation" ) {
        ofstream fout("unitbuf.tmp");;
        fout << unitbuf;
        fout << nounitbuf << "not flushed";
        
        ifstream fin("unitbuf.tmp");;
        string str;
        REQUIRE_FALSE( fin >> str );
        
        fout.close();
        fin.close();
        remove("unitbuf.tmp");
    }

}

TEST_CASE( "left", "[std] [streams] [manipulators]" ) {
    
    SECTION( "left adjust text" ) {
        ostringstream sout;

        sout << setw(10) << left << "ABCDE";
        
        REQUIRE( "ABCDE     " == sout.str() ); 
    }

    SECTION( "left adjust number" ) {
        ostringstream sout;

        sout << setw(10) << left << 12345;
        
        REQUIRE( "12345     " == sout.str() ); 
    }

    SECTION( "left adjust text with custom fill character" ) {
        ostringstream sout;

        sout << setw(10) << left << setfill('@')  << "ABCDE";
        
        REQUIRE( "ABCDE@@@@@" == sout.str() ); 
    }

}

TEST_CASE( "right", "[std] [streams] [manipulators]" ) {
    
    SECTION( "right adjust text" ) {
        ostringstream sout;

        sout << setw(10) << right << "ABCDE";
        
        REQUIRE( "     ABCDE" == sout.str() ); 
    }

    SECTION( "right adjust number" ) {
        ostringstream sout;

        sout << setw(10) << right << 12345;
        
        REQUIRE( "     12345" == sout.str() ); 
    }

    SECTION( "left adjust text with custom fill character" ) {
        ostringstream sout;

        sout << setw(10) << right << setfill('@')  << "ABCDE";
        
        REQUIRE( "@@@@@ABCDE" == sout.str() ); 
    }

}

TEST_CASE( "internal", "[std] [streams] [manipulators]" ) {
    
    SECTION( "insert fill character at internal point for negative integer" ) {
        ostringstream sout;

        sout << setw(10) << internal << -1;
        
        REQUIRE( "-        1" == sout.str() ); 
    }

    SECTION( "insert fill character at internal point for hex output" ) {
        ostringstream sout;

        sout << setw(10) << internal << hex << showbase << 255;
        
        REQUIRE( "0x      ff" == sout.str() ); 
    }

    SECTION( "insert fill character at internal point for money output" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << setw(10) << internal << showbase << put_money(cents);

        REQUIRE( "$     1.99" == sout.str() );
    }

}
