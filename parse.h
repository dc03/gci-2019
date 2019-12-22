# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

# ifndef __FILE_PARSE_H
#   define __FILE_PARSE_H

#include <bits/stdc++.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <process.h>

#include ".\units_handlers.h"

auto parse_file(std::string&, handlers::BaseHandler&, 
    handlers::UnitHandler&) -> void;
auto line_type(std::string&) -> int64_t;
auto is_num(std::string&) -> bool;
auto is_name(std::string&) -> bool;
auto tokenise_base(std::string&, handlers::BaseHandler&) -> void;
auto tokenise_names(std::string&, handlers::BaseHandler&,
    handlers::UnitHandler&) -> void;
auto set_values(std::string&, handlers::BaseHandler&, 
    handlers::UnitHandler&) -> void;

auto parse_file(std::string &file_name, handlers::BaseHandler &bases, 
    handlers::UnitHandler &units) -> void 
{
    std::ifstream fin(file_name.c_str(), std::ios::in);
    if (!fin)
        throw std::runtime_error{ "File not found / doesn't exist" };
    auto line_number{ 1 };
    while (!fin.eof())
    {
        std::string line{};
        std::getline(fin, line);
        // std::cout << line << '\n';
        switch (line_type(line))
        {
            case 0: // comment
                break;

            case 1: // base unit definition
                try
                { tokenise_base(line, bases); }
                catch (const std::runtime_error &e)
                {
                    std::cerr << "\n---\nError: " << e.what() << '\n' 
                    << file_name  << ":" << line_number << ": " << line 
                    << "\nSyntax must be \"base\" \"unit\" <unit_name>"
                    << "\n where <unit_name> is the name of a base unit\n"
                    << "---\n";
                    std::exit(-1);
                }
                catch (const std::exception &e)
                { std::cerr << "\nError: " << e.what() << "\n---\n"; }
                break;

            case 2: // unit name definitions
                try
                { tokenise_names(line, bases, units); }
                catch (const std::runtime_error &e)
                {
                    std::cerr << "\n---\nError: " << e.what() << '\n' 
                    << file_name << ":" << line_number << ": " << line
                    << "\nUnknown / incorrect syntax\n---\n";
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "\n---\nError: " << e.what() << '\n' 
                    << file_name << ":" << line_number << ": " << line 
                    << "\nUnknown unit\n---\n";
                }
                catch (const std::exception &e)
                { std::cerr << "\nError: " << e.what() << "\n---\n"; }
                break;

            case 3: // unit values definition
                try
                { set_values(line, bases, units); }
                catch (const std::runtime_error &e)
                {
                    std::cerr << "\n---\nError: " << e.what() << '\n' 
                    << file_name << ":" << line_number << ": " << line << 
                    "\n---\n";
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "\n---\nError: " << e.what() << '\n' 
                    << file_name << ":" << line_number << ": " << line
                    << "\nUnknown base unit\n---\n"; 
                }
                catch (const std::exception &e)
                { std::cerr << "\nError: " << e.what() << "\n---\n"; }
                break;

            default: // anything else
                std::cerr << "\nError:\n" << file_name << ":" << line_number <<
                ": " << line << "\nUnkown syntax\n---\n";
                break;
        }
        line_number += 1;
    }
}

auto line_type(std::string &line) -> int64_t
{
    if (!line.size())
        return 0;
    std::stringstream stream{ line };
    std::string token;
    stream >> token;
    if (token == "#" || token.at(0) == '#')
        return 0;
    else if (token == "base")
        return 1;
    else if (is_num(token))
        return 3;
    else if (is_name(token))
        return 2;
    else
        return -1;
}

auto is_num(std::string &value) -> bool
{
    for (const auto &x: value)
        if (x < '0' || x > '9')
            return false;
    return true;
}

auto is_name(std::string &name) -> bool
{ return !is_num(name); }

auto tokenise_base(std::string &line, handlers::BaseHandler &base_units)
    -> void
{
    std::stringstream stream{ line };
    std::string base, unit, unit_name;
    stream >> base >> unit >> unit_name;
    if ((base == "base") && (unit == "unit"))
        base_units.add_base(unit_name, 1);
    else
        throw std::runtime_error{ "Unknown / incorrect syntax" };
}

auto tokenise_names(std::string &line, handlers::BaseHandler &bases,
    handlers::UnitHandler &units) -> void
{
    std::stringstream stream{ line };
    std::string unit_name, can, be, unit_names;
    stream >> unit_name >> can >> be >> unit_names;
    if (can != "can" && be != "be")
        throw std::runtime_error{ "Unknown / incorrect syntax" };
    try
    {
        auto base = bases.get_base(unit_name);
        base -> set_names(unit_names);
    }
    catch (const std::invalid_argument &)
    {
        try
        {
            auto unit = units.get_unit(unit_name);
            unit -> set_names(unit_names);
        }
        catch (const std::invalid_argument &e)
        { throw e; }
        catch (const std::exception &e)
        { std::cerr << e.what() << '\n'; }
    }
    catch (const std::exception &e)
    { std::cerr << e.what() << '\n'; }
    
}

auto set_values(std::string &line, handlers::BaseHandler &bases,
    handlers::UnitHandler &units) -> void
{
    std::stringstream stream{ line };
    std::string unit_name, equal, base_name;
    double value, value_in_base;
    stream >> value >> unit_name >> equal >> value_in_base >> base_name;
    if (equal != "=")
        throw std::runtime_error{ "Unknown / incorrect syntax" };
    try
    {
        auto base{ bases.get_base(base_name) };
        try
        { auto unit{ units.get_unit(unit_name) }; }
        catch (const std::invalid_argument &e)
        { 
            units.add_unit(base_name, bases, (value_in_base / value), 
                unit_name); 
        }
        catch (const std::exception &e)
        { std::cerr << e.what() << '\n'; }
    }
    catch (std::invalid_argument &e)
    { throw e; }
    catch (const std::exception& e)
    { std::cerr << e.what() << '\n'; }
}

# endif // parse.h

# endif // check for c++ standard