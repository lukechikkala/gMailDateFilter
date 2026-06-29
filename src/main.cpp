
#include <chrono>
#include <cstdio>
#include <ctime>
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

std::optional<Date> Read_Date( const std::string& prompt )
{
    std::cout << prompt;
    std::string input;
    if( !( std::cin >> input ) )
    {
        std::cout << "Invalid Input" << '\n';
        return std::nullopt;
    }

    std::cout << input << std::endl;

    return std::nullopt;
}

void Date_Filter()
{
    std::cout << "gMail Date Filter" << '\n';

    auto from   = Read_Date( "Start Date [ DD.MM or DD.MM.YYYY ]: " );
    if( !from ) return;

    auto to     = Read_Date( "  End Date [ DD.MM or DD.MM.YYYY ]: " );
    if( !to ) return;
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

