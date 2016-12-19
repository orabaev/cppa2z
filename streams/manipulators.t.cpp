#include <catch.hpp>
#include <sstream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <iostream>

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

#ifdef __linux__
        REQUIRE( "$1.99     " == sout.str() );
#else
        REQUIRE( "$     1.99" == sout.str() );
#endif
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

TEST_CASE( "fixed", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to fixed " ) {
        ostringstream sout;
        
        sout << fixed << 0.1 << ' ' << 2.0011 << ' ' << 2.123456789;
        
        REQUIRE( "0.100000 2.001100 2.123457" == sout.str() ); 
    }

}

TEST_CASE( "scientific", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to scientific " ) {
        ostringstream sout;
        
        sout << scientific << 0.1 << ' ' << 0.0011 << ' ' << 1234.0001;

        REQUIRE( "1.000000e-01 1.100000e-03 1.234000e+03" == sout.str() ); 
    }

}

TEST_CASE( "hexfloat", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to hexfloat " ) {
        ostringstream sout;
        
        sout << hexfloat << 0.1 << ' ' << 0.0011 << ' ' << 1234.0001;

        REQUIRE( "0x1.999999999999ap-4 0x1.205bc01a36e2fp-10 0x1.348001a36e2ebp+10" == sout.str() ); 
    }

}

TEST_CASE( "defaultfloat", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to defaultfloat" ) {
        ostringstream sout;
        
        sout << defaultfloat << 0.1 << ' ' << 2.0011 << ' ' << 2.123456789;
        
        REQUIRE( "0.1 2.0011 2.12346" == sout.str() ); 
    }

}

TEST_CASE( "ws", "[std] [streams] [manipulators]" ) {
    
    SECTION( "discards leading white space from input stream" ) {
        istringstream sin{"    Hello C++\n   ws not discarded\n  ws discarded"};
        string str;

        getline(sin >> ws, str);  
        REQUIRE( "Hello C++" == str );

        getline(sin, str);  
        REQUIRE( "   ws not discarded" == str );


        getline(sin >> ws, str);  
        REQUIRE( "ws discarded" == str );
    }

}

TEST_CASE( "ends", "[std] [streams] [manipulators]" ) {
    
    SECTION( "insert null character" ) {
        ostrstream sout;

        sout << "0123456" << ends;
        const char* str = sout.str(); 
        
        REQUIRE( '\0' == str[7] );

        sout.freeze(false);
    }
 
}

TEST_CASE( "manipulator.flush", "[std] [streams] [manipulators]" ) {
    
    SECTION( "flush file stream to sync with underlying file" ) {
        ofstream fout("flush.tmp");
        REQUIRE( fout );
        fout << "abc"; 

        string str;
        ifstream fin("flush.tmp"); 
        REQUIRE_FALSE( fin >> str );
        fin.close();

        // flush ----
        REQUIRE( fout << flush );
        // ---- flush

        fin.open("flush.tmp");
        REQUIRE( fin >> str );

        REQUIRE( "abc" == str );
    }

    remove("flush.tmp");
}

TEST_CASE( "endl", "[std] [ostream] [misc]" ) {
    
    SECTION( "insert new line character flush file stream to sync with underlying file" ) {
        ofstream fout("endl.tmp");
        REQUIRE( fout );
        fout << "abc" << '\n'; 

        string str;
        ifstream fin("endl.tmp"); 
        REQUIRE_FALSE( fin >> str );
        fin.close();

        // endl ----
        fout << "def" << endl; 
        // ---- endl

        fin.open("endl.tmp");

        getline(fin, str);
        REQUIRE( "abc" == str );

        getline(fin, str);
        REQUIRE( "def" == str );
    }

    remove("endl.tmp");
}

TEST_CASE( "resetiosflags", "[std] [streams] [manipulators]" ) {
    
    SECTION( "reset formating flags" ) {
        ostringstream sout;

        sout << hex << showbase << uppercase 
             << 255 
             << resetiosflags(ios::hex | ios::showbase | ios::uppercase)
             << ' '
             << 255;
        
        REQUIRE( "0XFF 255" == sout.str() ); 
    }

}

TEST_CASE( "setiosflags", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set formating flags" ) {
        ostringstream sout;

        sout << 255 
             << ' '
             << resetiosflags(ios::dec)
             << setiosflags(ios::hex | ios::showbase | ios::uppercase)
             << 255;
        
        REQUIRE( "255 0XFF" == sout.str() ); 
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

TEST_CASE( "setfill", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default fill character for adjusted text" ) {
        ostringstream sout;

        sout << setw(25) << left << setfill('*') <<  "ABCDE";
        REQUIRE( "ABCDE********************" == sout.str() ); 

        sout.str(string{});
        sout << setw(25) << left << setfill(' ') <<  "ABCDE";
        REQUIRE( "ABCDE                    " == sout.str() ); 
    }

}

TEST_CASE( "setprecision", "[std] [streams] [manipulators]" ) {
   
    SECTION( "set default fill character for adjusted text" ) {
        ostringstream sout;
        const long double pi = 3.14159265358979;;
        
        sout << pi
             << ' '
             << setprecision(10) << pi
             << ' '
             << setprecision(15) << pi;

        REQUIRE( "3.14159 3.141592654 3.14159265358979" == sout.str() );
    }

}

TEST_CASE( "setw", "[std] [streams] [manipulators]" ) {
   
    SECTION( "set width for adjusted text" ) {
        ostringstream sout;
        
        sout << setw(1) << "ABC";
        REQUIRE( "ABC" == sout.str() );

        sout.str(string{});
        sout << setw(10) << "ABC";
        REQUIRE( "       ABC" == sout.str() );
    }

}

TEST_CASE( "put_money", "[std] [streams] [manipulators]" ) {

    SECTION( "us dollars" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 100099;

        sout << put_money(cents);
        REQUIRE( "1,000.99" == sout.str() );

        sout.str(string{});
        sout << showbase << put_money(cents);
        REQUIRE( "$1,000.99" == sout.str() );
    }

#ifndef __linux__
    SECTION( "russian rubbles" ) {
        ostringstream sout;
        sout.imbue(locale("ru_RU"));

        int kopecs = 100099;

        sout << put_money(kopecs);

        sout.str(string{});
        sout << showbase << put_money(kopecs);
        REQUIRE( "1 000,99 руб." == sout.str() );
    }
#endif

}

TEST_CASE( "get_money", "[std] [streams] [manipulators]" ) {

    SECTION( "us dollars" ) {
        istringstream sin{"$1,000.99"};
        sin.imbue(locale("en_US"));

        long double cents{};

        sin >> get_money(cents);
        REQUIRE( 100099.0 == cents );
    }

#ifndef __linux__
    SECTION( "russian rubbles" ) {
        istringstream sin{"1 000,99 руб."};
        sin.imbue(locale("ru_RU"));

        long double kopecs{};

        sin >> get_money(kopecs);
        REQUIRE( 100099.0 == kopecs );
    }
#endif

}

TEST_CASE( "put_time", "[std] [streams] [manipulators]" ) {
    
    tm date_time{};
    date_time.tm_year  = 116; // 2016     Since 1900
    date_time.tm_mon   = 11;  // December [0,11]
    date_time.tm_mday  = 18;  //          [1, 31]
    date_time.tm_hour  = 9;   //          [0, 23]
    date_time.tm_min   = 3;   //          [0, 59]
    date_time.tm_sec   = 7;   //          [0, 54]
    date_time.tm_wday  = 0;   // Saturday [0, 6]
    date_time.tm_yday  = 352; //          [0, 365]
    date_time.tm_isdst = 0;   // Off      

    SECTION( "format as 2016/12/18 09:03:07" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%Y/%m/%d %H:%M:%S");
        
        REQUIRE( "2016/12/18 09:03:07" == sout.str() ); 
    }

    SECTION( "format as Sunday, December 18, 2016" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%A, %B %d, %Y");
        
        REQUIRE( "Sunday, December 18, 2016" == sout.str() ); 
    }

    SECTION( "format as Sun, Dec 18" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%a, %b %d");
        
        REQUIRE( "Sun, Dec 18" == sout.str() ); 
    }

#ifndef __linux__
    SECTION( "format as Sun Dec 18 09:03:07 2016" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        sout << put_time(&date_time, "%c");

        REQUIRE( "Sun Dec 18 09:03:07 2016" == sout.str() );
    }
#endif

    SECTION( "format as 12/18/16" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%D");

        REQUIRE( "12/18/16" == sout.str() ); 
    }

}

TEST_CASE( "get_time", "[std] [streams] [manipulators]" ) {
    
    SECTION( "parse as 2016/12/18 09:03:07" ) {
        istringstream sin{"2016/12/18 09:03:07"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%Y/%m/%d %H:%M:%S");
        
        REQUIRE( 116 == date_time.tm_year ); 
        REQUIRE( 11  == date_time.tm_mon ); 
        REQUIRE( 18  == date_time.tm_mday ); 
        REQUIRE( 9   == date_time.tm_hour ); 
        REQUIRE( 3   == date_time.tm_min ); 
        REQUIRE( 7   == date_time.tm_sec ); 
    }

    SECTION( "parse as Sunday, December 18, 2016" ) {
        istringstream sin{"Sunday, December 18, 2016"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%A, %B %d, %Y");
        
        REQUIRE( 116 == date_time.tm_year ); 
        REQUIRE( 11  == date_time.tm_mon ); 
        REQUIRE( 18  == date_time.tm_mday ); 
        REQUIRE( 0   == date_time.tm_wday ); 
    }

    SECTION( "parse as Sun, Dec 18" ) {
        istringstream sin{"Sun, Dec 18"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%a, %b %d");
        
        REQUIRE( 11  == date_time.tm_mon ); 
        REQUIRE( 18  == date_time.tm_mday ); 
        REQUIRE( 0   == date_time.tm_wday ); 
    }

#ifndef __linux__ 
    SECTION( "parse as Sun Dec 18 09:03:07 2016" ) { //review
        istringstream sin{"Sun Dec 18 09:03:07 2016"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%c");
        
        REQUIRE( 116 == date_time.tm_year ); 
        REQUIRE( 11  == date_time.tm_mon ); 
        REQUIRE( 18  == date_time.tm_mday ); 
        REQUIRE( 9   == date_time.tm_hour ); 
        REQUIRE( 3   == date_time.tm_min ); 
        REQUIRE( 7   == date_time.tm_sec ); 
        REQUIRE( 0   == date_time.tm_wday ); 
    }
#endif

    SECTION( "parse as 12/18/16" ) {
        istringstream sin{"12/18/16"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%D");
       
#ifdef __linux__ 
        REQUIRE( 16 == date_time.tm_year );
        REQUIRE( 11  == date_time.tm_mon );
        REQUIRE( 18  == date_time.tm_mday );
#else
        REQUIRE( 116 == date_time.tm_year );
        REQUIRE( 11  == date_time.tm_mon );
        REQUIRE( 18  == date_time.tm_mday );
#endif
    }

}

TEST_CASE( "quoted", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< quoted" ) {
        ostringstream sout;

        sout << quoted("Hello C++");

        REQUIRE( "\"Hello C++\"" == sout.str() );
    }

    SECTION( "<< quoted custom delimiter" ) {
        ostringstream sout;

        sout << quoted("Hello C++", '|');

        REQUIRE( "|Hello C++|" == sout.str() );
    }

    SECTION( "<< quoted with default escape" ) {
        ostringstream sout;

        sout << quoted("Hello \\ C++");

        REQUIRE( "\"Hello \\\\ C++\"" == sout.str() );
    }

    SECTION( "<< quoted with custom delimiter and escape" ) {
        ostringstream sout;

        sout << quoted("Hello ? C++", '|', '?');

        REQUIRE( "|Hello ?? C++|" == sout.str() );
    }

    SECTION( ">> quoted" ) {
        istringstream sin{"\"Hello C++\""};
        string str;
            
        sin >> quoted(str);

        REQUIRE( "Hello C++" == str );
    }

    SECTION( ">> quoted custom delimiter" ) {
        istringstream sin{"|Hello C++|"};
        string str;
            
        sin >> quoted(str, '|');

        REQUIRE( "Hello C++" == str );
    }

    SECTION( ">> quoted with default escape" ) {
        istringstream sin{"\"Hello \\\\ C++\""};
        string str;

        sin >> quoted(str);

        REQUIRE( "Hello \\ C++" == str );
    }

    SECTION( ">> quoted with custom delimiter and escape" ) {
        istringstream sin{"|Hello ?? C++|"};
        string str;

        sin >> quoted(str, '|', '?');

        REQUIRE( "Hello ? C++" == str );
    }

}
