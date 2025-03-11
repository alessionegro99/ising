#pragma once

#include "io.hpp"

struct physicalParameters
{
    std::map<std::string, double> variables;

    bool loadFromFile(const std::string &filename);
    double get(const std::string &variable) const;
    void printAll() const;
};

bool physicalParameters::loadFromFile(const std::string &file_name)
{
    std::ifstream file(file_name);

    if (!file)
    {
        std::cerr << "Error: Could not open the file \"" << file_name << "\"." << std::endl;
        std::cerr << "Fatal error in function \"" << __func__ << "\": " << "Something went wrong." << std::endl;
        std::exit(1);
        }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string variable;
        double value;

        if (!(iss >> variable >> value))
        {
            std::cerr << "Warning: Could not parse line: \"" << line << "\"." << std::endl;
            continue;
        }

        variables[variable] = value;
    }
    return true;
}

double physicalParameters::get(const std::string &variable) const
{
    auto it = variables.find(variable);
    if (it != variables.end())
    {
        return it->second;
    }
    else
    {
        std::cerr << "Warning: Variable \"" << variable << "\" not found." << std::endl;
        return 0.0;
        /* Remove eventually */
        //std::cerr << "Fatal error in function \"" << __func__ << "\": " << "Something went wrong." << std::endl;
        //std::exit(1);
    }
}

void physicalParameters::printAll() const
{
    for (const auto &[key, value] : variables)
    {
        std::cout << key << " = " << value << std::endl;
    }
}