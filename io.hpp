#pragma once

#include "physicalParameters.hpp"

// Specifies when and where a fatal error occurred.
void fatalError(const std::string &message, const std::string &function_name)
{
    std::cerr << "Fatal error in function \"" << function_name << "\": " << message << std::endl;
    std::exit(1);
}

// Checks whether a file is empty or not.
bool isFileEmpty(const std::string &file_name)
{
    std::ifstream file(file_name, std::ios::ate);
    if (!file)
    {
        std::cerr << "Error: could not open the file \"" << file_name << "\"." << std::endl;
        fatalError("something went wrong", __func__);
    }

    return file.tellg() == 0;
}

// Prints usage specific information.
void printUsage(const std::string &program_name)
{
    std::cout << "Usage: " << program_name << " -f <filename>" << std::endl;
}

