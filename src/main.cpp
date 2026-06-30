
#include <chrono>
#include <cstdio>
#include <ctime>
#include <exception>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

struct Date
{
    int Day;
    int Month;
    int Year;
};

int Current_Year()
{
    auto        now = std::chrono::system_clock::now();
    std::time_t t   = std::chrono::system_clock::to_time_t( now );
    std::tm local{};
    localtime_s( &local, &t );
    return local.tm_year + 1900;
}

bool Is_Leap( int year )
{
    return ( year % 4 == 0 && year % 100 != 0 ) || ( year % 400 == 0 );
}

Date Parse_And_Validate( const std::string& input )
{
    // Should accept DD.MM where YYYY is taken as the current Year.
    // or DD.MM.YYYY where the user specifically be able to give the year.

    static const std::regex pattern( R"((\d{1,2})\.(\d{1,2})(?:\.(\d{4}))?)" );
    std::smatch match;

    if ( !std::regex_match( input, match, pattern ) )
        throw std::runtime_error( "Invalid Input: Expected DD.MM or DD.MM.YYYY" );

    const int day   = std::stoi( match[ 1 ]);
    const int month = std::stoi( match[ 2 ]);
          int year  = Current_Year();
    if ( match[ 3 ].matched )
        year = std::stoi( match[ 3 ] );

    if ( month < 1 || month > 12 )
        throw std::runtime_error( "Invalid Month: " + std::to_string( month ) );

    static constexpr int days_in_month[] = {
          31, 28, 31, 30, 31, 30, 31
        , 31, 30, 31, 30, 31
    };
    int day_max = days_in_month[ month - 1 ];
    if ( month == 2 && Is_Leap( year ) )
        day_max = 29;

    if ( day < 1 || day > day_max )
        throw std::runtime_error( "Invald Day: " + std::to_string( day   )
                                + " for month: " + std::to_string( month )
                );

    return { day, month, year };
}

bool Is_Before( const Date& Start, const Date& End )
{
        if( Start.Year  != End.Year  ) return Start.Year  < End.Year;
        if( Start.Month != End.Month ) return Start.Month < End.Month;
    return  Start.Day   <= End.Day;
}

std::optional<Date> Read_Date( const std::string& prompt )
{
    std::cout << prompt;
    std::string input;
    if( !( std::cin >> input ) )
    {
        std::cout << "Invalid Input" << '\n';
        return std::nullopt;
    }

    try
    {
        return Parse_And_Validate( input );
    }
    catch ( const std::exception& e )
    {
        std::cout << e.what() << '\n';
        return std::nullopt;
    }

}

void Date_Filter()
{
    std::cout << "gMail Date Filter" << '\n';

    auto from   = Read_Date( "Start Date [ DD.MM or DD.MM.YYYY ]: " );
    if( !from ) return;

    auto to     = Read_Date( "  End Date [ DD.MM or DD.MM.YYYY ]: " );
    if( !to ) return;

    if( !Is_Before( *from, *to ) )
    {
        std::cout << "Error: End Date must be after Start Date";
        return;
    }
}

int main()
{
    try
    {
        Date_Filter();
    }
    catch ( const std::exception& e )
    {
        std::cerr << "Unexpected Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

