/* See LICENSE for license details */

// v0.1.1

#include <bits/stdc++.h>
#include <cstring>
#include <stdexcept>

#include ".\units_handlers.h"
#include ".\unit_converter.h"

auto main() -> int32_t
{
    handlers::BaseHandler bases;
    handlers::UnitHandler units;
    std::string file_name{ "conversion_table.txt" };
    // std::cout << "Enter the file name: ";
    // std::getline(std::cin, file_name);
    try
    { init_convert(file_name, bases, units); }
    catch (const std::runtime_error &e)
    { 
        std::cerr << "\n---\nError: " << e.what() << '\n';
        return 0;
    }
    while (true)
    {
        std::string query;
        std::cout << "\nEnter the query:\n";
        std::getline(std::cin, query);
        if (query == "exit")
            break;
        try
        { convert(query, bases, units); }
        catch (std::invalid_argument &e)
        { std::cerr << "\n---\nError: " << query << "\n : " << e.what() 
            << "\n---\n"; }
        catch (const std::exception &e)
        { std::cerr << "\n---\nError: " << e.what() << "\n---\n"; }
    }
    return 0;
}