/* See LICENSE for license details */

# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

# ifndef __UNITS_H
#   define __UNITS_H

#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <memory>
#include <stdexcept>

namespace unit
{
    class BaseUnit
    {
        std::string m_name{};
        double m_value{ 0 };
        std::vector<std::string> m_names{};
    public:
        BaseUnit(std::string, double);
        auto set_names(std::string) -> void;
        auto get_name() -> std::string;
        auto get_names() -> std::vector<std::string>;
        auto get_val() -> double;
    };

    class Unit
    {
        std::string m_name{};
        std::shared_ptr<BaseUnit> m_base_unit{ nullptr };
        double m_value_in_base{ 0 };
        std::vector<std::string> m_names{};
    public:
        Unit(std::shared_ptr<BaseUnit>, double, std::string);
        auto try_into(Unit &other) -> bool;
        auto get_base() -> std::shared_ptr<BaseUnit>&;
        auto get_val_as_base() -> double;
        auto set_names(std::string) -> void;
        auto get_name() -> std::string;
        auto get_names() -> std::vector<std::string>;
    };

    BaseUnit::BaseUnit(std::string name, double value): m_name{ name }, 
                                                        m_value{ value } {}

    auto BaseUnit::set_names(std::string names) -> void
    {
        auto names_str = new char[names.length()];
        std::strcpy(names_str, names.c_str());
        auto token = std::strtok(names_str, ",");
        while (token != NULL)
        {
            m_names.push_back(std::string{ token });
            token = std::strtok(NULL, ",");
        }
        delete[] names_str;
    }

    auto BaseUnit::get_name() -> std::string
    { return this -> m_name; }

    auto BaseUnit::get_names() -> std::vector<std::string>
    { return this -> m_names; }

    auto BaseUnit::get_val() -> double
    { return this -> m_value; }

    Unit::Unit(std::shared_ptr<BaseUnit> base, double value_base, 
        std::string name): m_base_unit{ base }, m_value_in_base{ value_base },
                           m_name{ name } {}

    auto Unit::get_base() -> std::shared_ptr<BaseUnit>&
    { return this -> m_base_unit; }

    auto Unit::get_val_as_base() -> double
    { return this -> m_value_in_base; }

    auto Unit::set_names(std::string names) -> void
    {
        auto names_str = new char[names.length()];
        std::strcpy(names_str, names.c_str());
        auto token = std::strtok(names_str, ",");
        while (token != NULL)
        {
            m_names.push_back(std::string{ token });
            token = std::strtok(NULL, ",");
        }
        delete[] names_str;
    }

    auto Unit::get_name() -> std::string
    { return this -> m_name; }

    auto Unit::get_names() -> std::vector<std::string>
    { return this -> m_names; }
};

namespace handlers
{
    class BaseHandler
    {
        std::vector<std::shared_ptr<unit::BaseUnit>> m_base_units;

    public:
        BaseHandler() {}
        BaseHandler(BaseHandler&) = delete;
        BaseHandler& operator = (BaseHandler&) = delete;
        auto add_base(std::string, double) -> void;
        auto update_base(std::string, std::string) -> void;
        auto get_base(std::string) -> std::shared_ptr<unit::BaseUnit>&;
        auto check_unit(std::string) -> bool;
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
        auto check_unit(std::string) -> bool;
    };

    auto BaseHandler::add_base(std::string unit_name, double value) -> void
    {
        auto ptr = std::make_shared<unit::BaseUnit>(unit_name, value);
        this -> m_base_units.push_back(ptr);
    }

    auto BaseHandler::update_base(std::string unit_name, std::string names)
    -> void
    {
        for (auto &base: this -> m_base_units)
            if (base -> get_name() == unit_name)
            {
                base -> set_names(names);
                break;
            }
    }

    auto BaseHandler::get_base(std::string unit_name) 
    -> std::shared_ptr<unit::BaseUnit>&
    {
        for (auto &base: this -> m_base_units)
            if (base -> get_name() == unit_name)
                return base;
            else
                for (auto &name: base -> get_names())
                    if (name == unit_name)
                        return base;
        throw std::invalid_argument{ "Base unit not found" }; // not found
    }

    auto BaseHandler::check_unit(std::string unit_name) -> bool
    {
        for (auto &base: this -> m_base_units)
            if (base -> get_name() == unit_name)
                return true;
            else
                for (auto &name: base -> get_names())
                    if (name == unit_name)
                        return true;
        return false;
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
            std::cerr << "\n---\nError: " << e.what() << "\nUnknown base unit: "
            << base_unit << "\n---\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    auto UnitHandler::update_unit(std::string unit_name, std::string names)
        -> void
    {
        for (auto &unit: this -> m_units)
            if (unit -> get_name() == names)
            {
                unit -> set_names(names);
                break;
            }
    }

    auto UnitHandler::get_unit(std::string unit_name) 
        -> std::shared_ptr<unit::Unit>&
    {
        for (auto &unit: this -> m_units)
            if (unit -> get_name() == unit_name)
                return unit;
            else
                for (auto &name: unit -> get_names())
                    if (name == unit_name)
                        return unit;
        throw std::invalid_argument{ "Unit not found" };
    }

    auto UnitHandler::check_unit(std::string unit_name) -> bool
    {
        for (auto &unit: this -> m_units)
            if (unit -> get_name() == unit_name)
                return true;
            else
                for (auto &name: unit -> get_names())
                    if (name == unit_name)
                        return true;
        return false;
    }
};

# endif // file_parser.h

# endif // c++ standard checking