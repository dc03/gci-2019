# pragma once

# if __cplusplus < 201703L

# error Expected c++17 standard 

# else

#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <memory>

# ifndef __UNITS_H
#   define __UNITS_H

namespace unit
{
    class BaseUnit;
    class Unit;

    class BaseUnit
    {
        std::vector<std::string> m_names{};
    public:
        BaseUnit(std::string);
        auto get_names() -> std::vector<std::string>;
    };

    class Unit
    {
        BaseUnit *m_base_unit{ nullptr };
        double m_value_in_base{ 0 };
        std::vector<std::string> m_names{};
    public:
        Unit(BaseUnit*, double, std::string);
        auto try_into(Unit &other) -> bool;
        auto get_base() -> BaseUnit*;
        auto get_val_as_base() -> double;
        auto get_names() -> std::vector<std::string>;
    };

    BaseUnit::BaseUnit(std::string names)
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

    auto BaseUnit::get_names() -> std::vector<std::string>
    { return this -> m_names; }

    Unit::Unit(BaseUnit *base, double value_base, std::string names): 
        m_base_unit{ base }, m_value_in_base{ value_base } 
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

    auto Unit::get_base() -> BaseUnit*
    { return this -> m_base_unit; }

    auto Unit::get_val_as_base() -> double
    { return this -> m_value_in_base; }

    auto Unit::get_names() -> std::vector<std::string>
    { return this -> m_names; }
};

# endif // file_parser.h

# endif // c++ standard checking