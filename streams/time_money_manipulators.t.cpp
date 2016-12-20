#include <catch.hpp>
#include <sstream>

using namespace std;

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
