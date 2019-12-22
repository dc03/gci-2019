# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

# ifndef __FILE_PARSE_H
#   define __FILE_PARSE_H

#include <bits/stdc++.h>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include ".\units.h"

auto parse_file(std::string&) -> bool;
auto line_type(std::string&) -> int64_t;
auto is_num(std::string&) -> bool;
auto is_name(std::string&) -> bool;
auto tokenise_base(std::string&, handlers::BaseHandler&) -> void;

namespace handlers
{
    class BaseHandler
    {
        std::vector<std::shared_ptr<unit::BaseUnit>> m_base_units;

    public:
        BaseHandler() {}
        BaseHandler(BaseHandler&) = delete;
        BaseHandler& operator = (BaseHandler&) = delete;
        auto add_base(std::string) -> void;
        auto update_base(std::string, std::string) -> void;
        auto get_base(std::string) -> std::shared_ptr<unit::BaseUnit>&;
    };

    class UnitHandler
    {
        std::vector<std::shared_ptr<unit::Unit>> m_units;

    public:
        UnitHandler() {}
        UnitHandler(UnitHandler&) = delete;
        UnitHandler& operator = (UnitHandler&) = delete;
        auto add_unit(std::string, BaseHandler&, double, std::string) -> void;
        auto update_unit(std::string, std::string) -> void;
        auto get_unit(std::string) -> std::shared_ptr<unit::Unit>&;
    };

    auto BaseHandler::add_base(std::string unit_name) -> void
    {
        auto ptr = std::make_shared<unit::BaseUnit>(unit_name);
        this -> m_base_units.push_back(ptr);
    }

    auto BaseHandler::update_base(std::string unit_name, std::string names)
    -> void
    {
        for (auto &x: this -> m_base_units)
            if (x -> get_name() == unit_name)
            {
                x -> set_names(names);
                break;
            }
    }

    auto BaseHandler::get_base(std::string unit_name) 
    -> std::shared_ptr<unit::BaseUnit>&
    {
        for (auto &x: this -> m_base_units)
            if (x -> get_name() == unit_name)
                return x;
            else
                for (auto &names: x -> get_names())
                    if (!std::strcmp(names.c_str(), unit_name.c_str()))
                        return x;
        throw std::invalid_argument{ "Base unit not found" }; // not found
    }

    auto UnitHandler::add_unit(std::string base_unit, BaseHandler &bases,
        double value_in_base, std::string unit_name) -> void
    {
        try
        {
            auto base{ bases.get_base(base_unit) };
            auto unit = std::make_shared<unit::Unit>(base, value_in_base,
                unit_name);
            this -> m_units.push_back(unit);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: " << e.what() << "\nUnknown base unit: "
            << base_unit;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    auto UnitHandler::update_unit(std::string unit_name, std::string names)
        -> void
    {
        for (auto &x: this -> m_units)
            if (x -> get_name() == names)
            {
                x -> set_names(names);
                break;
            }
    }

    auto UnitHandler::get_unit(std::string unit_name) 
    -> std::shared_ptr<unit::Unit>&
    {
        for (auto &x: this -> m_units)
            if (x -> get_name() == unit_name)
                return x;
            else
                for (auto &name: x -> get_names())
                    if (name == unit_name)
                        return x;
        throw std::invalid_argument{ "Unit not found" };
    }
};

auto parse_file(std::string &file_name) -> bool
{
    std::ifstream fin(file_name.c_str(), std::ios::in);
    handlers::BaseHandler bases;
    handlers::UnitHandler units;
    auto line_number{ 1 };
    while (!fin.eof())
    {
        std::string line{};
        std::getline(fin, line);
        switch (line_type(line))
        {
            case 0: // comment
            case 1: // base unit definition
                try
                { tokenise_base(line, bases); }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Error: " << e.what() << '\n' << file_name 
                    << ":" << line_number << ": " << line 
                    << "\nSyntax must be \"base\" \"unit\" <unit_name>";
                }
                catch (const std::exception &e)
                { std::cerr << "Error: " << e.what(); }
            case 2: // unit name definitions
            case 3: // unit values definition
            default: // anything else
        }
        line_number += 1;
    }
}

auto line_type(std::string &line) -> int64_t
{
    std::stringstream stream{ line };
    std::string token;
    stream >> token;
    if (!std::strcmp(token.c_str(), "#"))
        return 0;
    else if (!std::strcmp(token.c_str(), "base"))
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
{
    for (const auto &x: name)
        if (x >= '0' && x <= '9')
            return false;
    return true;
}

auto tokenise_base(std::string &line, handlers::BaseHandler &base_units)
    -> void
{
    std::stringstream stream{ line };
    std::string base, unit, unit_name;
    stream >> base >> unit >> unit_name;
    if (!std::strcmp(base.c_str(), "base") && 
        !std::strcmp(unit.c_str(), "unit"))
        base_units.add_base(unit_name);
    else
        throw std::invalid_argument{ "Wrong line syntax" };
}

# endif

# endif