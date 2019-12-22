# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

# ifndef __UNIT_CONVERTER_H
#   define __UNIT_CONVERTER_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <sstream>

#include ".\units_handlers.h"
#include ".\parse.h"

enum class QueryTypes
{
    unit_to_unit,
    unit_to_base,
    base_to_unit,
    base_to_base,
    malformed
};

auto init_convert(std::string&, handlers::BaseHandler&, handlers::UnitHandler&) 
    -> void;
auto convert(std::string&, handlers::BaseHandler&, handlers::UnitHandler&) 
    -> void;
auto check_query(std::string&, handlers::BaseHandler&, handlers::UnitHandler&) 
    -> QueryTypes;
auto tokenise_query(std::string&, std::string&, double&, std::string&) -> void;

auto init_convert(std::string &file_name, handlers::BaseHandler &bases, 
    handlers::UnitHandler &units) -> void
{ parse_file(file_name, bases, units); }

auto convert(std::string &query, handlers::BaseHandler &bases, 
    handlers::UnitHandler &units) -> void
{
    try
    {
        auto check { check_query(query, bases, units) };
        std::string unit_from_name{}, unit_to_name{};
        double value{};
        tokenise_query(query, unit_from_name, value, unit_to_name);
        switch (check)
        {
            case QueryTypes::unit_to_unit:
            {
                if (units.get_unit(unit_from_name) -> get_base() -> get_name()
                !=  units.get_unit(unit_to_name) -> get_base() -> get_name())
                    throw std::invalid_argument{ "Incompatible types" };
                auto unit_from_val{ units.get_unit(unit_from_name) 
                                    -> get_val_as_base() };
                auto unit_to_val{ units.get_unit(unit_to_name)
                                    -> get_val_as_base() };
                auto result{ unit_from_val * value / unit_to_val };
                std::cout << value << ' ' << unit_from_name << " = " <<
                    result << ' ' << unit_to_name << '\n';
            }
                break;
            case QueryTypes::unit_to_base:
            {
                if (units.get_unit(unit_from_name) -> get_base() -> get_name() 
                !=  bases.get_base(unit_to_name) -> get_name())
                    throw std::invalid_argument{ "Incompatible types" };
                auto unit_from_val{ units.get_unit(unit_from_name) 
                                    -> get_val_as_base() };
                std::cout << value << ' ' << unit_from_name << " = " <<
                    (value * unit_from_val) << ' ' << unit_to_name << '\n';
            }
                break;
            case QueryTypes::base_to_unit:
            {
                if (bases.get_base(unit_from_name) -> get_name() != 
                    units.get_unit(unit_to_name) -> get_base() -> get_name())
                    throw std::invalid_argument{ "Incompatible types" };
                auto unit_to_val{ units.get_unit(unit_to_name) 
                                    -> get_val_as_base() };
                std::cout << value << ' ' << unit_from_name << " = " <<
                    (value / unit_to_val) << ' ' << unit_to_name << '\n';
            }
                break;
            case QueryTypes::base_to_base:
            {
                if (bases.get_base(unit_from_name) -> get_name() != 
                    bases.get_base(unit_to_name) -> get_name())
                    throw std::invalid_argument{ "Incompatible types" };
                std::cout << value << ' ' << unit_from_name << " = " <<
                    value << ' ' << unit_to_name << '\n';
            }
                break;
            case QueryTypes::malformed:
            {
                std::cerr << "\n---\nError: " << query << ": malformed query"
                << "\n Queries must be in the form of: \n"
                << "  <value> <unit_from> \"to\" (or) \"as\" (or) \"from\""
                   " (or) \"in\" <unit_to>, where:\n"
                   "  value: value of unit\n"
                   "  unit_from: unit to be converted from"
                   "  unit_to: unit to be converted to\n---\n\n";
            }
                break;
        }
    }
    catch (const std::runtime_error &e)
    { std::cerr << "\n---\nError: " << query << ": " << e.what() << '\n'; }
    catch (const std::exception &e)
    { std::cerr << "\nError: " << e.what() << "\n---\n"; }
}

auto check_query(std::string &query, handlers::BaseHandler &bases,
    handlers::UnitHandler &units) -> QueryTypes
{
    std::stringstream stream{ query };
    std::string unit_from_name, op, unit_to_name;
    double from_val;
    stream >> from_val >> unit_from_name >> op >> unit_to_name;
    if ((op != "to") && (op != "as") && (op != "from") && (op != "in"))
        return QueryTypes::malformed;
    else if (units.check_unit(unit_from_name) && units.check_unit(unit_to_name))
        return QueryTypes::unit_to_unit;
    else if (units.check_unit(unit_from_name) && bases.check_unit(unit_to_name))
        return QueryTypes::unit_to_base;
    else if (bases.check_unit(unit_from_name) && units.check_unit(unit_to_name))
        return QueryTypes::base_to_unit;
    else if (bases.check_unit(unit_from_name) && bases.check_unit(unit_to_name))
        return QueryTypes::base_to_base;
    else
        return QueryTypes::malformed;
}

auto tokenise_query(std::string &query, std::string &unit_from_name, 
    double &value, std::string &unit_to_name) -> void
{
    std::stringstream stream{ query };
    std::string op;
    stream >> value >> unit_from_name >> op >> unit_to_name;
}

# endif // unit_converter.h

# endif // 