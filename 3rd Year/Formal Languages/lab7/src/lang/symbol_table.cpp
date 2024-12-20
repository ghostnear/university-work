#include "lang/symbol_table.hpp"

int any_to_int(std::any value)
{
    return std::any_cast<int>(value);
}

double any_to_double(std::any value)
{
    return std::any_cast<double>(value);
}

float any_to_float(std::any value)
{
    return std::any_cast<float>(value);
}

std::string any_to_string(std::any value)
{
    return std::any_cast<std::string>(value);
}