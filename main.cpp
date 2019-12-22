/* See LICENSE for license details */

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
    init_convert(file_name, bases, units);
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
        { std::cerr << "\n---\nError: " << query << "\n : " << e.what(); }
        catch (const std::exception &e)
        { std::cerr << "\nError: " << e.what() << "\n---\n"; }
    }
    return 0;
}