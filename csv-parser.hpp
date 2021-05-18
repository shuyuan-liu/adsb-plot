#pragma once
#include <string>
#include <vector>

namespace CsvParser
{
void parse (std::string& input_line, std::vector<std::string>& parsed_fields);
}