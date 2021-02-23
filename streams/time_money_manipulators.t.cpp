#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "put_money", "[std] [streams] [manipulators]" ) {

    SECTION( "us dollars" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 100099;

        sout << put_money(cents);
        REQUIRE( sout.str() == "1,000.99" );

        sout.str(string{});
        sout << showbase << put_money(cents);
        REQUIRE( sout.str() == "$1,000.99" );
    }

#ifndef __linux__
    SECTION( "russian rubbles" ) {
        ostringstream sout;
        sout.imbue(locale("ru_RU"));

        int kopecs = 100099;

        sout << put_money(kopecs);

        sout.str(string{});
        sout << showbase << put_money(kopecs);
        REQUIRE( sout.str() == "1 000,99 руб." );
    }
#endif

}

TEST_CASE( "get_money", "[std] [streams] [manipulators]" ) {

    SECTION( "us dollars" ) {
        istringstream sin{"$1,000.99"};
        sin.imbue(locale("en_US"));

        long double cents{};

        sin >> get_money(cents);
        REQUIRE( cents == 100099.0 );
    }

#ifndef __linux__
    SECTION( "russian rubbles" ) {
        istringstream sin{"1 000,99 руб."};
        sin.imbue(locale("ru_RU"));

        long double kopecs{};

        sin >> get_money(kopecs);
        REQUIRE( kopecs == 100099.0 );
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
        
        REQUIRE( sout.str() == "2016/12/18 09:03:07" ); 
    }

    SECTION( "format as Sunday, December 18, 2016" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%A, %B %d, %Y");
        
        REQUIRE( sout.str() == "Sunday, December 18, 2016" ); 
    }

    SECTION( "format as Sun, Dec 18" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%a, %b %d");
        
        REQUIRE( sout.str() == "Sun, Dec 18" ); 
    }

#ifndef __linux__
    SECTION( "format as Sun Dec 18 09:03:07 2016" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        sout << put_time(&date_time, "%c");

        REQUIRE( sout.str() == "Sun Dec 18 09:03:07 2016" );
    }
#endif

    SECTION( "format as 12/18/16" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));
        
        sout << put_time(&date_time, "%D");

        REQUIRE( sout.str() == "12/18/16" ); 
    }

}

TEST_CASE( "get_time", "[std] [streams] [manipulators]" ) {
    
    SECTION( "parse as 2016/12/18 09:03:07" ) {
        istringstream sin{"2016/12/18 09:03:07"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%Y/%m/%d %H:%M:%S");
        
        REQUIRE( date_time.tm_year == 116 ); 
        REQUIRE( date_time.tm_mon  ==  11 ); 
        REQUIRE( date_time.tm_mday ==  18 ); 
        REQUIRE( date_time.tm_hour ==   9 ); 
        REQUIRE( date_time.tm_min  ==   3 ); 
        REQUIRE( date_time.tm_sec  ==   7 ); 
    }

    SECTION( "parse as Monday, January 18, 2016" ) {
        istringstream sin{"Monday, January 18, 2016"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%A, %B %d, %Y");
        
        REQUIRE( date_time.tm_year == 116 ); 
        REQUIRE( date_time.tm_mon  ==   0 ); 
        REQUIRE( date_time.tm_mday ==  18 ); 
        REQUIRE( date_time.tm_wday ==   1 ); 
    }

    SECTION( "parse as Sun, Dec 18" ) {
        istringstream sin{"Sun, Dec 18"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%a, %b %d");
        
        REQUIRE( date_time.tm_mon  == 11 ); 
        REQUIRE( date_time.tm_mday == 18 ); 
        REQUIRE( date_time.tm_wday ==  0 ); 
    }

#ifndef __linux__ 
    SECTION( "parse as Sun Dec 18 09:03:07 2016" ) { //review
        istringstream sin{"Sun Dec 18 09:03:07 2016"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%c");
        
        REQUIRE( date_time.tm_year == 116 ); 
        REQUIRE( date_time.tm_mon  ==  11 ); 
        REQUIRE( date_time.tm_mday ==  18 ); 
        REQUIRE( date_time.tm_hour ==   9 ); 
        REQUIRE( date_time.tm_min  ==   3 ); 
        REQUIRE( date_time.tm_sec  ==   7 ); 
        REQUIRE( date_time.tm_wday ==   0 ); 
    }
#endif

    SECTION( "parse as 12/18/16" ) {
        istringstream sin{"12/18/16"};
        sin.imbue(locale("en_US"));
        
        tm date_time{};
        sin >> get_time(&date_time, "%D");
       
#ifdef __linux__ 
        REQUIRE( date_time.tm_year == 16 );
        REQUIRE( date_time.tm_mon  == 11 );
        REQUIRE( date_time.tm_mday == 18 );
#else
        REQUIRE( date_time.tm_year == 116 );
        REQUIRE( date_time.tm_mon  ==  11 );
        REQUIRE( date_time.tm_mday ==  18 );
#endif
    }

}
