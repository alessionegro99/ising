#pragma once

#include <iostream>
#include <fstream>

void fatalError(const std::string &message, const std::string &function_name);
bool isFileEmpty(const std::string &file_name);