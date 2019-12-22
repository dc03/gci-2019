# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <memory>
#include <stdexcept>

# ifndef __UNITS_H
#   define __UNITS_H

namespace unit
{
    class BaseUnit
    {
        std::string m_name{};
        std::vector<std::string> m_names{};
    public:
        BaseUnit(std::string);
        auto set_names(std::string) -> void;
        auto get_name() -> std::string;
        auto get_names() -> std::vector<std::string>;
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
        auto get_base() -> std::shared_ptr<BaseUnit>;
        auto get_val_as_base() -> double;
        auto set_names(std::string) -> void;
        auto get_name() -> std::string;
        auto get_names() -> std::vector<std::string>;
    };

    BaseUnit::BaseUnit(std::string name): m_name{ name } {}

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

    Unit::Unit(std::shared_ptr<BaseUnit> base, double value_base, 
        std::string name): m_base_unit{ base }, m_value_in_base{ value_base },
                           m_name{ name } {}

    auto Unit::get_base() -> std::shared_ptr<BaseUnit>
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

# endif // file_parser.h

# endif // c++ standard checking